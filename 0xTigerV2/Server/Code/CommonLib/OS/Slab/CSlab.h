/*  ���ߣ�		�ֶ�ƽ lin_style@foxmail.com                                                        
	����ʱ�䣺	2010/06/29                                                        
    ����˵����  һ�����ٷ��䡢�ͷŲ�ͬ��С�ڴ����͵Ķ�����м�㣬һЩԭ��ο�linux�е�slab,slub.����ά��slab
	Ҫ��:       32λ��������û���⣬��ȻҲ�����64λ��ƣ�����û��ʽ�����
				ֻ����С�˻���������


	���Ե��ڵĲ������Ƿ����������(Ĭ�Ϲر�)��
					�Ƿ���CPU��Ե(Ĭ�ϴ�)
					�Ƿ�������ҳ�����(Ĭ�Ϲر�)
					�Ƿ�Ԥ�����ڴ�(Ĭ�Ϲر�)
*/

#pragma once


#include "Singleton.h"
#include "OSOther.h"
#include "CVirAlloc.h"
#include "MTASSERT.h"
/*
	CONFIG_SLAB_DEBUG	:�ܿ���
	DEBUG_DEFAULT_FALGS :��Ҫ���ٵľ���DEBUG��ǩ
*/
#define CONFIG_SLAB_DEBUG


#ifdef CONFIG_SLAB_DEBUG

	#define DEBUG_DEFAULT_FALGS (SLAB_RED_ZONE | CPU_RUN_ID | GC_PARTIAL_PAGE )

#else
	
	#define DEBUG_DEFAULT_FALGS 0

#endif 

/*
	��Ҫ���Ե�DEBUG��ǩ������˳��Ϊ
	0x1,0x2,0x4,0x8
	0x10,0x20,0x40,0x80
	0x100,0x200,0x300,0x400
	...
*/
#define SLAB_RED_ZONE 0x1	//0x1	�����������
#define CPU_RUN_ID 0x2		//0x2	�������CPU����,��������֤�л�ʱ����ʹ���ϲ���������ҳ����Ҫ��ˢ
#define GC_PARTIAL_PAGE 0x4 //0x4	��������ҳ�����


namespace name_slab
{
	/*
		KMEM_COUNT����ÿ��Kmem֧�ֵĶ����С,��λΪbyte
		���㷽ʽΪ2^KMEM_COUNT�η�.
	*/
	const int KMEM_GRAIN_BYTE[] = {4, 8, 16, 32, 64, 128, 256, 512, 
		                           1024,  1024*2,  1024*4, 1024*8, 1024*16
								   };
	const int KMEM_COUNT = sizeof(KMEM_GRAIN_BYTE)/sizeof(*KMEM_GRAIN_BYTE);
	/*
		����ҳ��ı�����.�������⵽����ҳ�����MIN_PARTIALʱ���Զ����ҳ������ͷŸ�ϵͳ
	*/
	const unsigned int BAD_ALIEN_MAGIC = 0x01020304;
	/*
		ÿ��kmem�����ֳ��ȣ��������
	*/
	const int KMEM_NAME_SIZE = 24;
	/*
		���������ڴ�İٷֱȣ�����Ľ��ͷŸ�����ϵͳ
		50:�ٷ�֮��ʮ
	*/
	const int MIN_PARTIAL_PER = 50;  
};

class CBadAlienMagic
{
public:
	CBadAlienMagic()
	{
		m_nOffset=0;
	}

	unsigned int GetBadAlienMagic()
	{
		++m_nOffset;
		return name_slab::BAD_ALIEN_MAGIC+m_nOffset;
	}
	unsigned int m_nOffset;
};

/*	
	����Э�����£�redУ��������������verify��ʱ��ֱ�ӴӺ��濪ʼ����
    |..............|   |..............|
	|list|object....red|list|object....red|list|object....red
*/
class CSlabCache
{
public:
	CSlabCache();

private:

public:
	unsigned int m_nOffset;
	void* m_pFreeList;
	VIR_PAGE_HEAD *m_pPage;

private:
	
	
};

class CSlabNode
{
public:
	CSlabNode();
	void PushPageHead(VIR_PAGE_HEAD* p);
	VIR_PAGE_HEAD* PopPageHead();
	void PopPageHead(VIR_PAGE_HEAD* p);	
	unsigned long GetPartialCount();

private:
	void __PushPageHead(VIR_PAGE_HEAD* p);
	VIR_PAGE_HEAD* __PopPageHead();	

public:


private:
	unsigned long m_nPartialListCount;
	list_head m_PartialList;
	CFastLock m_FastLock;
};


class CKmem
{
public:
	~CKmem();

	/*
		strKmemName:Kmem�����֣��������
		nKmemSizeKB:Kmem�Ĵ�С
		nAllocMB/nAllocGrainKB:   Kmem������alloc��ʼ������
	*/
	void Init(const char* strKmemName, int nObjectSizeByte, int nObjectMetaSizeByte, CVirAlloc* pVirAlloc);

	void* KmemMalloc();
	void KmemFree(void *p);

	CSlabNode* GetSlabNode();
	CVirAlloc* GetVirAlloc();

	int GetObjectSizeByte();
	int GetObjectMetaSizeByte();
	const char*GetKmemName();
	unsigned long GetMinPartial();
	void SetMinPartial(int nMinPartial);

private:	
	CSlabCache *GetCpuSlab();
	CSlabCache *GetSlab(int nIndex);

	void InitMemoryList(void *p);
	/*
		MallocPage:��freelist�������ݵ�ʱ�򣬴ӽڵ�����ھ��л�ȡ��ҳ��
	*/
	void* MallocPage(CSlabCache *s);
	/* 
		�ṩCSlabCache��������ִֹ�����̱߳�CPU�л�
	*/
	void* MallocPartialNode(CSlabCache *s);
	void* MallocOSPage(CSlabCache *s);

	bool FreeLocal(VIR_PAGE_HEAD* pPage,void *p);
	void FreeNode(VIR_PAGE_HEAD* pPage, void *p);

	/*
		p:һ��������object��ʼ��ַ������magic�ĵ�ַ
	*/
	void* GetBadAlienMagicAddr(void *p);
public:
	/*
		debug��Ҫ��һЩ����(��Ϊ��Ч����ͳ��)
		m_nHasUsePage: ʹ���˶���ҳ��
		m_nHasFreePage: �ͷ��˶��ٴ�ҳ��
		m_nCountMalloc: �����˶��ٴη���
		m_nCountMallocPartial: ���ھ��з����˶��ٴ�
		m_nCountFree:   �����˶��ٴ��ͷ�
		m_nBadAlienMagic:�ڴ��Ƿ��ƻ�������У��
	*/
	unsigned long m_nHasUsePage;
	unsigned long m_nHasFreePage;
	unsigned long m_nCountMalloc;
	unsigned long m_nCountMallocPartial;
	unsigned long m_nCountFree;
	unsigned long m_nBadAlienMagic;

private:
	/*
		m_nObjectSizeByte :����ÿ������Ĵ�С
		m_nObjectMetaSizeByte: ����Meta������
	*/	
	int m_nObjectSizeByte;
	int m_nObjectMetaSizeByte;
	char m_szName[name_slab::KMEM_NAME_SIZE];

	CSlabCache *m_pSlabCache;
	CSlabNode  m_SlabNode;
	CVirAlloc  *m_pWinVirAlloc;

	/*
		m_nMinPartial:���ڴ�ֵ�ĺ��ҳ�涼���ͷŸ�ϵͳ
	*/
	unsigned long m_nMinPartial;
	int n_mCPUNumberOf;
	CFastLock m_FastLock;
};

/*
	�����ӡ�������CKmem��ʹ�����
*/
class CKmemManager:public Singleton<CKmemManager>
{
public:
	void TracerMe();
	void Tracer();

	CKmemManager();
	
	void* KmemMalloc(int nSizeByte);
	void KmemFree(void *p);

private:
	void Init();

	/*
		���ذ���meta data�Լ��ֽڶ����Ĵ�С
	*/
	int CalcSize(int nSize);
	CKmem* GetKmem(int nSizeByte);
	int GetKmemIndex(int nSizeByte);

public:

private:
	CKmem m_Kmem[name_slab::KMEM_COUNT];
	CVirAllocManager m_VirAllocManager;

};

#define g_KmemManager CKmemManager::getSingleton()