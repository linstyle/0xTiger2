#include "stdafx.h"
#include "CMyStackWalker.h"
#include "CWindowsSlab.h"
#include <stdio.h>
#include <assert.h>
CSlabCache::CSlabCache()
{
	m_pPage = NULL;
}

CSlabCache::~CSlabCache()
{
	FREE_NULL(m_pPage);
}

/*
	CSlabNode
*/
CSlabPartial::CSlabPartial()
{
	INIT_LIST_HEAD(&m_PartialList);
	m_nPartialListCount = 0;
}

CSlabPartial::~CSlabPartial()
{
	VIR_PAGE_HEAD *pPage;

	while ( NULL!= (pPage=PopPageHead()) )
	{
		FREE_NULL(pPage);
	}
}

VIR_PAGE_HEAD* CSlabPartial::PopPageHead()
{
	VIR_PAGE_HEAD* p;

	p = __PopPageHead();

	return p;
}

void CSlabPartial::PopPageHead(VIR_PAGE_HEAD* p)
{
	list_del(&p->m_PageListNode);	
	--m_nPartialListCount;
}

void CSlabPartial::PushPageHead(VIR_PAGE_HEAD* p)
{		
	__PushPageHead(p);
}

unsigned long CSlabPartial::GetPartialCount()
{
	return m_nPartialListCount;
}

VIR_PAGE_HEAD* CSlabPartial::__PopPageHead()
{
	list_head *pListIte;
	VIR_PAGE_HEAD *pPageHead;

	pListIte = list_get(&m_PartialList);
	if(NULL==pListIte)
	{
		return NULL;
	}

	pPageHead = list_entry_offset(pListIte, VIR_PAGE_HEAD, m_PageListNode);


	--m_nPartialListCount;
	return pPageHead;
}

void CSlabPartial::__PushPageHead(VIR_PAGE_HEAD* p)
{	
	IFm( NULL==p)
	{
		return;
	}

	++m_nPartialListCount;
	list_add(&p->m_PageListNode,  &m_PartialList);
}
CKmem::CKmem()
{
	m_pSlabCache = 0;
}

CKmem::~CKmem()
{
	delete []m_pSlabCache;
}

void CKmem::Init(long nMallocObjectSizeByte)
{
	//��ȡCPU����
	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);

	int nCPUNumberOf=0;

	nCPUNumberOf = sinf.dwNumberOfProcessors;

	m_nCPUNumberOf = nCPUNumberOf;

	//����SlabCache
	m_pSlabCache = new CSlabCache[m_nCPUNumberOf];

	//����pageֵ
	m_nSingleObjectSizeByte = nMallocObjectSizeByte;
	//����ҳ����Ϊm_nMallocObjectSizeByte��100��
	long nSumPageSizeByte = name_slab::CalcSingleObjectSize(nMallocObjectSizeByte)*100 + sizeof(VIR_PAGE_HEAD);
	m_nSinglePageSizeKB = (long)(nSumPageSizeByte/ 1024.0 + 1); //��ֹ����nSumPageSizeByte��С���
	m_nSinglePageSizeKB = _ALIGN(m_nSinglePageSizeKB, __ALIGN_SIZE_PAGE);

	m_nSingleMaxCountObject = ( m_nSinglePageSizeKB*1024-sizeof(VIR_PAGE_HEAD) ) / name_slab::CalcSingleObjectSize(nMallocObjectSizeByte);

	//��ʼ����һ��page
	for (int i=0; i<m_nCPUNumberOf; ++i)
	{
		MallocPage(&m_pSlabCache[i]);
	}

	InitD();
}

void CKmem::InitD()
{
	m_nDMallocCount = 0;
	m_nDFreeCount = 0;
	m_nDPartialMallocCount = 0;
	m_nDPartialFreeCount = 0;
}

void CKmem::TraceMe()
{
	LOGMN("m_nSingleObjectSizeByte:%d, m_nSinglePageSizeKB:%d, m_nSingleMaxCountObject:%d\n",
			   m_nSingleObjectSizeByte, m_nSinglePageSizeKB, m_nSingleMaxCountObject);
	LOGMN("MallocCount:%d, FreeCount:%d,Malloc Elapse Memery(MB):%f\n", m_nDMallocCount, m_nDFreeCount,
		  m_nDMallocCount*m_nSingleObjectSizeByte/1024.0/1024.0);
	LOGMN("PartialMallocCount:%d, PartialFreeCount:%d\n", m_nDPartialMallocCount, m_nDPartialFreeCount);
	LOGMN("PartialCount:%d\n", m_SlabPartial.GetPartialCount());
	LOGMN("-----------------------------\n");
}

void* CKmem::Kmalloc()
{
	__try
	{
		m_FastLock.Lock();

		CSlabCache *s = GetCpuSlab();
		if(NULL==s->m_pPage->m_pFreeList)
		{
			assert(0==s->m_pPage->m_nFreeObject);
			s->m_pPage->m_nState = STATE_ALL_USER_LOCK;
			if(NULL==MallocPage(s))
			{
				m_FastLock.UnLock();
				return NULL;
			}
		}

		void *p = s->m_pPage->m_pFreeList;
		s->m_pPage->m_pFreeList = (void*)(*(long*)p);
		--s->m_pPage->m_nFreeObject;

		++m_nDMallocCount;

		m_FastLock.UnLock();

		return p;
	}
	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))
	{
		return NULL;
	}
}

void  CKmem::Kfree(void *p)
{
	IFm( NULL==p)
	{
		return;
	}

	__try
	{
		if( NULL==p )
		{
			printf("Err, CKmem::KmemFree:NULL==p\n");
			return;
		}

		/*
			1.�ж��Ƿ�͵�ǰҳ����ȣ�������ͷ�
			2.����ȣ�������Ƿ�����slab
			3.��pagehead,���뵽�ھӽڵ�
		*/
		VIR_PAGE_HEAD* pPage = name_slab::OffsetPageHead(p);
		if( NULL==pPage )
		{
			printf("Err, CKmem::KmemFree:NULL==pPage\n");
			return;
		}

		if( DEBUG_SLAB_FALGS & SLAB_RED_ZONE )
		{		
			if( name_slab::HEAD_BAD_ALIEN_MAGIC!=name_slab::OffsetBadMagic(p) )
			{
				printf("Err, CKmem::FreeLocal:m_nBadAlienMagic\n");
				return;
			}
		}

		m_FastLock.Lock();

		if(false==FreeNode(pPage,p))
		{
			//ʧ��++
		}
		
		++m_nDFreeCount;
		m_FastLock.UnLock();
	}
	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))
	{
		
	}
}

bool CKmem::FreeNode(VIR_PAGE_HEAD* pPage,void *p)
{
	IFm(NULL==pPage || NULL==p)
	{
		return false;
	}

	++pPage->m_nFreeObject;

	//˵�����ڵ�ǰslab��
	if (STATE_CACHE_LOCK!=pPage->m_nState)
	{
		return FreePartialNode(pPage, p);
	}

	//ֱ�Ӳ���
	*(long*)p = (long)pPage->m_pFreeList;
	pPage->m_pFreeList = p;

	return true;
}

bool CKmem::FreePartialNode(VIR_PAGE_HEAD* pPage, void *p)
{
	IFm(NULL==pPage || NULL==p)
	{
		return false;
	}

	void *pPrior = pPage->m_pFreeList;

	*(long*)p = (long)pPage->m_pFreeList;
	pPage->m_pFreeList = p;

	/*
		��ҳ��ĵ�һ���ͷţ����뵽partial
	*/
	if( NULL==pPrior )
	{
		pPage->m_nState = STATE_PARTIAL_LOCK;
		m_SlabPartial.PushPageHead(pPage);
	}

	++m_nDPartialFreeCount;

	FreeOSPage(pPage);

	return true;
}

void CKmem::FreeOSPage(VIR_PAGE_HEAD* pPage)
{
	IFm(NULL==pPage)
	{
		return;
	}


	if( !(DEBUG_SLAB_FALGS & SLAB_GC_PARTIAL) )
	{
		return;
	}

	if (pPage->m_nFreeObject==m_nSingleMaxCountObject
		&& m_SlabPartial.GetPartialCount() >= name_slab::FREE_KEEP_PARTIAL )
	{
		m_SlabPartial.PopPageHead(pPage);
		FREE_NULL(pPage);
	}
	
}

void* CKmem::MallocPage(CSlabCache *s)
{
	IFm(NULL==s)
	{
		return NULL;
	}
	/*
		1.���Ϊ�գ���Ѱ���ھӽڵ�
					����ھӽڵ�Ϊ�գ������ڴ�
		2.�����Ϊ�գ�ֱ�Ӳ���������
	*/	
	VIR_PAGE_HEAD* pPage;

	pPage=MallocPartialNode();
	if( NULL==pPage )
	{
		pPage=MallocOSPage();
		IFm( NULL==pPage )			
		{
			return NULL;
		}
	}

	IFm(STATE_CACHE_LOCK != pPage->m_nState)
	{
		return NULL;
	}

	pPage->m_nState = STATE_CACHE_LOCK;

	s->m_pPage = pPage;

	return s->m_pPage->m_pFreeList;	
}

VIR_PAGE_HEAD* CKmem::MallocPartialNode()
{
	VIR_PAGE_HEAD *pPage = m_SlabPartial.PopPageHead();
	if (NULL==pPage)
	{
		return NULL;
	}
	
	IFm(STATE_PARTIAL_LOCK==pPage->m_nState)
	{
		return NULL;
	}

	++m_nDPartialMallocCount;
	return pPage;
}

VIR_PAGE_HEAD* CKmem::MallocOSPage()
{
	void *p = malloc(m_nSinglePageSizeKB*1024);
	IFm(NULL==p)
	{
		return NULL;
	}

	InitNewOSPage(p);

	return (VIR_PAGE_HEAD *)p;
}

void CKmem::InitNewOSPage(void *p)
{
	IFm(NULL==p)
	{
		return;
	}

	//�Ȳ��һ��ͷ
	VIR_PAGE_HEAD *pPage = (VIR_PAGE_HEAD*)p;

	pPage->Init(m_nSingleMaxCountObject, this, (void*)( (long)p+sizeof(VIR_PAGE_HEAD) ) );
	InitMemeryOSPage(pPage);
}

void CKmem::InitMemeryOSPage(VIR_PAGE_HEAD *pPage)
{
	IFm(NULL==pPage)
	{
		return;
	}

	void *p = pPage->m_pFreeList;

	for (int i=0; i<m_nSingleMaxCountObject; ++i)
	{	
		//���׳���,2��memcpy����CalcSingleObjectHeadSize��С������assert
		int nVerifyLen=0;
		if( DEBUG_SLAB_FALGS & SLAB_RED_ZONE )
		{
			memcpy(p, &name_slab::HEAD_BAD_ALIEN_MAGIC, sizeof(name_slab::HEAD_BAD_ALIEN_MAGIC) );
			p = (void*)( (long)p + sizeof(name_slab::HEAD_BAD_ALIEN_MAGIC) );
			nVerifyLen += sizeof(name_slab::HEAD_BAD_ALIEN_MAGIC);
		}

		memcpy(p, &pPage, sizeof(pPage));
		p =(void*)( (long)p + sizeof(pPage) );
		nVerifyLen += sizeof(pPage);

		assert( nVerifyLen==name_slab::CalcSingleObjectHeadSize() );

		//��¼������һ�������ڴ��ַ������Ҫ������һ�������ڴ��ַ��ͷ��
		*(long*)p = (long)p + m_nSingleObjectSizeByte+name_slab::CalcSingleObjectHeadSize();
		p = (void*)( (long)p + m_nSingleObjectSizeByte ) ;
	}

	p = (void*)( (long)p - m_nSingleObjectSizeByte ) ;
	*(long*)p = NULL;

	//��һ����������headsize
	pPage->m_pFreeList = (void*)( (long)pPage->m_pFreeList+name_slab::CalcSingleObjectHeadSize());
}

CSlabCache *CKmem::GetCpuSlab()
{
	int i=name_slab::GetCPURunId();
	if( DEBUG_SLAB_FALGS & SLAB_CPU_RUN_ID )
	{
		//printf("CKmem::GetCpuSlab:%d\n", i);
	}
	else
	{
		i = 0;
	}
	return &m_pSlabCache[i];
}

CSlabCache *CKmem::GetCpuSlab(int nIndex)
{
	IFm(nIndex<m_nCPUNumberOf || nIndex<0)
	{
		return NULL;
	}

	if (nIndex>m_nCPUNumberOf || nIndex<0)
	{
		return NULL;
	}
	return &m_pSlabCache[nIndex];
}
