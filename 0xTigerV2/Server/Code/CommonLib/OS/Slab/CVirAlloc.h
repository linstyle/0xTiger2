/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/29                                                         
    ����˵����  ��Windows��������һ����װ
				�õ�������Ҫ�����˵�ַ�ϵ�Ԥ����������������ͷ�
				ÿ��Ĭ�ϵ�λ����Ϊһҳ(������λ�����,32λΪ4KB��
				���ڴ��ڵ�λ���������룬��ҳ��ͷ��������Ϣ��¼��ʣ���ߵ��߼�һ��
*/
#include "GlobalType.h"
#include "Singleton.h"
#include "LinuxList.h"
#include "CLock.h"

#include <vector>

using namespace std;

namespace name_viralloc
{
	//��¼�ڴ�ҳ�Ƿ��ͷš������bitmap
	const int BIT_MAP_SIZE = sizeof(long);

	/*
		 ALLOC_GRAIN_SIZE_KB,ALLOC_MEM_SIZE_MB��ʾ��Ӧ�Ŀ����ȿ��Է�����ڴ�ռ��С
		 const int ALLOC_GRAIN_SIZE_KB[]={n};n��ʾ��֧�ֵ������󣬵�λkb
		 const int ALLOC_MEM_SIZE_MB[]=  {n};n��ʾ������ڴ����, ��λmb
	*/	
	const int ALLOC_GRAIN_SIZE_KB[]={16,1024*5};
	const int ALLOC_MEM_SIZE_MB[]=  {350,250};
	const int ALLOC_COUNT = sizeof(ALLOC_GRAIN_SIZE_KB)/sizeof(*ALLOC_GRAIN_SIZE_KB);

	//ÿ�������ȵĴ�С
	const int ALLOC_GRAIN_KB = __PAGE_SIZE_BYTE/1024;
	const int ALLOC_GRAIN_BYTE = ALLOC_GRAIN_KB*1024;
};

/*
	ҳ��ĵ�ǰ״̬
*/
enum PAGE_STATE
{
	SLAB_LOCK,		//��ĳ��SLAB����
	PARTIAL_LOCK,   //��Partial�ڵ���
	OS_LOCK,		//�黹��VirAlloc
};
/*
	ά������ÿ�������ȴ�С�ı�ͷ
*/
class CKmem;
struct VIR_PAGE_HEAD
{
	void Init() 
	{
		m_nHasUseObject = 0;
		m_pFreeList = NULL;
		m_pKmem = NULL;
		m_nState = OS_LOCK;
		INIT_LIST_HEAD(&m_PageNext);
	}
	int m_nHasUseObject;
	CKmem *m_pKmem;	
	void *m_pFreeList;

	PAGE_STATE m_nState;			//debug����
	struct list_head m_PageNext;
};


/*
	��ַ��һ����ѯ���ձ�
	������Ǹ������ȵ�����
*/
class CVirPageAddress
{
public:
	CVirPageAddress();
	struct ALLOC_ADDRESS
	{
		ALLOC_ADDRESS(unsigned long Start=0, unsigned long End=0)
		{
			m_Start = Start;
			m_End = End;
		}
		unsigned long m_Start;
		unsigned long m_End;
	};
	void Add(unsigned long Start, unsigned long End);
	int GetAddressIndex(unsigned long nAddress);

private:

public:

private:
	vector<ALLOC_ADDRESS> m_AllocAddress;
};

/*
	һ����ά��ҳ��ƫ�Ʊ�
	�������ʼ��ַ���г��ȣ����������ڵ�����
*/
class CVirPageTable
{
public:
	void Init(unsigned long Start, unsigned long Offset, unsigned long End);

	long ToPageOffset(void* pUnknowStart);

private:

public:

private:
	unsigned long m_Start;	//��ʼ��ַ
	unsigned long m_Offset;	//�г���
	unsigned long m_End;	//����ַ
};

/*
	��ַ��ҳ��ͷά��
*/
class CVirPageHead
{
public:
	~CVirPageHead();
	void Init(long nPageCount);
	VIR_PAGE_HEAD* GetPageHead(long nPageIndex);

private:

public:

private:
	VIR_PAGE_HEAD *m_pVirPageHead;
	long m_nPageCount;

};

class CVirPageAssis
{
public:	
	void InitPageHead(long nPageCount);
	void InitPageTable(unsigned long Start, unsigned long Offset, unsigned long End);

	/*
		ͨ���ڴ��ַ���ض�Ӧ��ҳ�����ƫ����
	*/
	VIR_PAGE_HEAD* GetPageHead(void *p);
	long GetPageHeadIndex(void* p);
private:
	

public:

private:
	CVirPageHead m_VirPageHead;
	CVirPageTable m_VirPageTable;
};

class CVirAlloc
{
public:
	CVirAlloc();
	~CVirAlloc();
	
	void Init(long nAllocMB, long nAllocGrainKB);
	/*
		MallocPage	: ����һ������ҳ
		FreePage	: �ͷŵ�ǰ��ַ���ڵ�����ҳ��
	*/
	VIR_PAGE_HEAD* MallocPage();
	void  FreePage(VIR_PAGE_HEAD *pPage);

	/*
		ͨ��һ����ַ�ҵ��õ�ַ���ڵ�ҳ��
	*/
	VIR_PAGE_HEAD* GetPageHead(void *p);

	/*
		��ȡ�ӿ�
	*/
	long GetAllocMemMB();
	long GetAllocGrainByte();
	long GetPageCount();
	long GetFreePageCount();
	long GetUsePageCount();
	void* GetAddressBegin();
	void* GetAddressEnd();

private:
	void InitAllocMem();
	void InitVirPageAssis();
	void InitPageOffset();
	
	long __MallocPage();
	long __FreePage(long nOffset);

	/*
		��������:��һ��λ��ʶ����˵����ǰ�����Ŀռ��Ƿ���Ч
		nOffset	:ҳ��������±꣬��0��ʼ
	*/
	void SetDebugFlag(long nOffset, long nFlag);
	long  GetDebugFlag(long nOffset);

public:
	/*
		 һ��ת����ַ��ͱ�ͷ
	*/
	CVirPageAssis m_VirPageAssis;

private:
	/*
		m_pAddressBegin	: ��ʼ��ַ
		m_PageOffset: ��ſ��е�ƫ����
	*/
	void* m_pAddressBegin;
	void* m_pAddressEnd;
	vector<long> m_PageOffset;

	/*
		m_pDebugFlag; : bitΪ��λ������Ƿ��ظ��ͷŻ��ȡ��0���ͷţ�1��ʾ�ѻ�ȡ
	*/
	long *m_pDebugFlag;
	long m_nUsePageCount;

	/*
		��alloc�������������ڴ�Ϳ�����
	*/
	long m_nAllocMemMB;
	long m_nAllocMemKB;
	unsigned long m_nAllocMemByte;

	long m_nAllocGrainKB;
	unsigned long m_nAllocGrainByte;

	CFastLock m_FastLock;
};

class CVirAllocManager
{
public:
	CVirAllocManager();

	void TracerMe();
	void Tracer();

	CVirAlloc* GetVirAlloc(long nSizeByte);
	VIR_PAGE_HEAD* GetPageHead(void *p);

private:
	void Init();
	long GetVirAllocIndex(long nSizeByte);

public:

private:
	CVirPageAddress m_VirPageAddress;
	CVirAlloc m_VirAlloc[name_viralloc::ALLOC_COUNT];
};

