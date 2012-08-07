#pragma once

#include <assert.h>
/*
	v1.0 2010/05/17
	�޸�Ϊһ����ʽ�档����¶�ڲ������ͣ����ⲿ����һ����Դ��š�����ֱ���ø�ֵ��=����ֹ�ƻ�ID��
*/

template<typename llist_t, int llist_size=100, bool bManual=false>
class CListOfArray
{
	//variable
public:
	struct ELEMENT
	{
		llist_t element;
		ELEMENT* pPre;
		ELEMENT* pNext;
	};

private:	
	unsigned int nMaxElementItem;
	ELEMENT *ElementData/*[llist_size]*/;//����ռ�

	ELEMENT ElementFreeHead;			//�����ָ����ͷ
	ELEMENT ElementUseHead;             //��ǰʹ�õ�ָ����ͷ

	int nFreeSum;
	int nUseSum;

	//function
public:
	CListOfArray()
	{
		nMaxElementItem = llist_size;
		if( false == bManual )
		{
			InitList();
		}		
	}
	~CListOfArray()
	{
		delete []ElementData;
	}

	/*
		ManualAlloct
		�ֶ������С
	*/
	void ManualAlloct(int nManualMaxItem)
	{
		nMaxElementItem = nManualMaxItem;
		InitList();
	}

	llist_t* GetMallocElement()
	{
		ELEMENT* p = MallocElement();

		if( NULL==p )
		{
			return NULL;
		}
		return &p->element;
	}
	
	void Erase(ELEMENT* p)
	{
		if( NULL==p )
		{
			return ;
		}

		ReleaseElement(p);
	}

	void Empty();

	ELEMENT* GetElementAtID(unsigned int nId)
	{
		if( nId>=GetMaxElementItem() )
			return NULL;

		return &ElementData[nId];	
	}

	llist_t* GetUseElementAtID(unsigned int nId)
	{
		if( nId>=GetMaxElementItem() )
			return NULL;

		return &ElementData[nId].element;
	}

	ELEMENT* GetListUseHead()
	{
		return ElementUseHead.pNext;
	}
	
	ELEMENT* GetListFreeHead()
	{
		return ElementFreeHead.pNext;
	}

	int GetSumElementUse()
	{
		return nUseSum;
	}

	int GetSumElementFree()
	{
		return nFreeSum;
	}

	unsigned int  GetMaxElementItem()
	{
		return nMaxElementItem;
	}

	/*
		�ṩֱ�Ӳ鿴Free��Use���������__nIdentiֵ
	*/
	void TracerMe();

private:		
	void InitList();
	ELEMENT* MallocElement();
	ELEMENT* ReleaseElement(ELEMENT *p);

	/*
		��ͷ������
		������NULL��β,��ʾ�޽ڵ㡣�����ڲ������ɾ����һЩ����Ҫ�ж��Ƿ��Ѿ���β��
		����linux��list����������ѭ����Ȼ���ж��Ƿ������ͷ��һ��
	*/
	void AddNodeToList(ELEMENT* const pNode, ELEMENT* const pDesListHead)
	{		
		pNode->pNext = pDesListHead->pNext;
		pNode->pPre  = pDesListHead;

		if( NULL!=pDesListHead->pNext )
		{
			pDesListHead->pNext->pPre = pNode;
		}

		pDesListHead->pNext = pNode;
	}
};


/*
	���Ի���������ȫ��������useָ��ͷΪ�գ�freeָ��ͷָ�������0��Ԫ��
*/
template <typename llist_t, int llist_size, bool bManual>
void CListOfArray<llist_t, llist_size, bManual>::InitList()
{
	assert( nMaxElementItem>0 );
	ElementData = new ELEMENT[nMaxElementItem];
	nUseSum = 0;
	nFreeSum = nMaxElementItem;

	for(unsigned int i=0; i<nMaxElementItem-1; ++i)
	{		
		ElementData[i].pNext = &ElementData[i+1];
	}

	ElementData[nMaxElementItem-1].pNext = NULL;

	ElementUseHead.pNext = NULL;
	ElementFreeHead.pNext = &ElementData[0];
}

/*
	ȡ��freeָ���һ��Ԫ��
*/
template <typename llist_t, int llist_size, bool bManual>
typename CListOfArray<llist_t, llist_size, bManual>::ELEMENT* CListOfArray<llist_t, llist_size, bManual>::MallocElement()
{	
	if( NULL==ElementFreeHead.pNext )
	{
		return NULL;
	}

	--nFreeSum;
	++nUseSum;
	
	ELEMENT* p = ElementFreeHead.pNext;
	ElementFreeHead.pNext = ElementFreeHead.pNext->pNext;

	AddNodeToList(p, &ElementUseHead);

	return p;
}

/*
	��Useָ�������룬���Ҽ���Freeָ��
*/
template <typename llist_t, int llist_size, bool bManual>
typename CListOfArray<llist_t, llist_size, bManual>::ELEMENT* CListOfArray<llist_t, llist_size, bManual>::ReleaseElement( ELEMENT *p)
{
	--nUseSum;
	++nFreeSum;
	ELEMENT *pResult = p->pNext;
	
	p->pPre->pNext = p->pNext;
	
	if( NULL!=p->pNext )
	{
		p->pNext->pPre = p->pPre;	
	}

	AddNodeToList(p, &ElementFreeHead);

	return pResult;
}

/*
	���ݷ����ǽ�ElementUseHeadֱ������ElementFreeHeadĩβ����ǰ������Ĭ��ͷ������
	
	���ǵ�ƽ��ʹ�ò��࣬Empty���ǲ���ʹ��.��ʱ����д��������Erase
*/
template <typename llist_t, int llist_size, bool bManual>
void CListOfArray<llist_t, llist_size, bManual>::Empty()
{
	ELEMENT* p = GetListHead();

	while( NULL!=p )
	{
		p = Erase(p);
		continue;

		p=p->pNext;
	}
}


template <typename llist_t, int llist_size, bool bManual>
void CListOfArray<llist_t, llist_size, bManual>::TracerMe()
{
	ELEMENT* p;

	printf("Use:\n");
	p = GetListUseHead();
	while(p!=NULL)
	{
		printf("%d,", p->element.__GetIdenti());
		p = p->pNext;
	}

	printf("\n");

	printf("Free:\n");
	p = GetListFreeHead();
	while(p!=NULL)
	{
		printf("%d,", p->element.__GetIdenti());
		p = p->pNext;
	}

	printf("\n");	
}

/*

struct IN_GLOBALRES_MROLE
{
	int nResIdenti;
};

IN_GLOBALRES_MROLE  InGlobalResMRole;

void CGlobalResMRole::Init()
{
	int nMax = CConfigManager::GetMaxMRoleCount();
	m_m_MRoleList.ManualAlloct( nMax );

	m_MRoleList_t *p = m_m_MRoleList.GetListFreeHead();
	for(int i=0; i<nMax; ++i)
	{
		p->element.MRoleHead.InGlobalResMRole.nResIdenti = i;
		p=p->pNext;
	}
}

CMRole* CGlobalResMRole::Add()
{
	return m_m_MRoleList.GetMallocElement();
}

CMRole* CMRoleManager::MRoleErase(CMRole *pMRole)
{
	m_MRoleList_t *p = m_m_MRoleList.GetElementAtID(pMRole->MRoleHead.InGlobalResMRole.nResIdenti);
	if( NULL==p )
	{
		printf("Warning, CGlobalResMRole::Erase: NULL==p. id:%d\n", pMRole->MRoleHead.InGlobalResMRole.nResIdenti);
		return;
	}

	m_m_MRoleList.Erase(p);
}



*/