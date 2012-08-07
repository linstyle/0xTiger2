#pragma once
//lindp
//2011.7.17
#include "GlobalType.h"
#include "CLock.h"
#include "LinuxList.h"
#include "CVirPageHead.h"
#include "CWindowsSlabDef.h"
#include "CLog2.0.h"

/*
	Slab����ҳ�棬��CPU�ҹ�
*/
class CSlabCache
{
public:
	CSlabCache();
	~CSlabCache();

private:

public:
	VIR_PAGE_HEAD *m_pPage;

private:

};

/*
	Slab�ھӽڵ�ҳ�����
*/
class CSlabPartial
{
public:
	CSlabPartial();
	~CSlabPartial();
	void PushPageHead(VIR_PAGE_HEAD* p);

	/*
		VIR_PAGE_HEAD* PopPageHead():		����ĳ��ҳ�棬����ɾ��
		void PopPageHead(VIR_PAGE_HEAD* p):	��ĳ��ҳ�����ɾ��
	*/
	VIR_PAGE_HEAD* PopPageHead();
	void PopPageHead(VIR_PAGE_HEAD* p);	

	//���ص�ǰ�����е�ҳ����
	unsigned long GetPartialCount();

private:
	/*
		�����������ԣ���װһ���ӿ�
	*/
	void __PushPageHead(VIR_PAGE_HEAD* p);
	VIR_PAGE_HEAD* __PopPageHead();	

public:


private:
	unsigned long m_nPartialListCount;
	list_head m_PartialList;
};


class CKmem
{
public:
	CKmem();
	~CKmem();

	void Init(long nMallocObjectSizeByte);
	//��ӡ���ڲ���Ϣ
	void TraceMe();

	void* Kmalloc();
	void  Kfree(void *p);

private:
	//��ʼ��DEBUG����
	void InitD();
	/* 
		MallocPage���ε���MallocPartialNode,MallocOSPage����֮ǰ��CSlabCache
		�Ѿ�ȷ����������ʱ����CPU�л������ǻ�����໺��
		��linux���и��жϵĺ���local_irq_save����ֹCPU�ж��л�,��ʱ��֪��windows����ʲôʵ��
	*/
	void* MallocPage(CSlabCache *s);
	VIR_PAGE_HEAD* MallocPartialNode();
	VIR_PAGE_HEAD* MallocOSPage();
	//�Դ�OS���������ҳ���ʼ��
	void InitNewOSPage(void *p);
	//�Դ�OS���������ҳ���ڴ��ʼ��
	void InitMemeryOSPage(VIR_PAGE_HEAD *pPage);

	/*
		FreeҲ��Mallocͬ�����ж�����
	*/
	bool FreeNode(VIR_PAGE_HEAD* pPage,void *p);
	bool FreePartialNode(VIR_PAGE_HEAD* pPage, void *p);
	void FreeOSPage(VIR_PAGE_HEAD* pPage);
	/*
		��������
	*/
	CSlabCache *GetCpuSlab();
	CSlabCache *GetCpuSlab(int nIndex);

public:
	/*
		debug�۲����
	*/
	//����ɹ���ʧ���˶��ٴ�
	//�ͷųɹ���ʧ���˶��ٴ�
	//��Partial�����˶��ٴ�
	int m_nDMallocCount;
	int m_nDFreeCount;
	int m_nDPartialMallocCount;
	int m_nDPartialFreeCount;

private:
	CSlabCache *m_pSlabCache;
	CSlabPartial m_SlabPartial;

	int m_nCPUNumberOf;

	CFastLock m_FastLock;
	/*
		����Ҫ�ļ���������
		m_nSingleObjectSizeByte:��ʾ��kmem�У�֧�ֵĵ��������С
		m_nSinglePageSizeKB:ÿ������ĵ���ҳ���С�����ݳ�ʼm_nMallocObjectSizeByteֵ���Զ��ж�
		m_nSingleMaxCountObject:����ǰ��2��ֵ���������ҳ���ܷ�����ٸ�����
	*/
	long m_nSingleObjectSizeByte;
	long m_nSinglePageSizeKB;	
	long m_nSingleMaxCountObject;
};
