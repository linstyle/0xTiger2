#pragma once

#include <assert.h>
/*
	v1.0 2010/05/17
	修改为一个正式版。不暴露内部的类型，在外部定义一个资源编号。不能直接用赋值号=，防止破坏ID号
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
	ELEMENT *ElementData/*[llist_size]*/;//数组空间

	ELEMENT ElementFreeHead;			//空余的指针链头
	ELEMENT ElementUseHead;             //当前使用的指针链头

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
		手动分配大小
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
		提供直接查看Free和Use两条链表的__nIdenti值
	*/
	void TracerMe();

private:		
	void InitList();
	ELEMENT* MallocElement();
	ELEMENT* ReleaseElement(ELEMENT *p);

	/*
		从头部加入
		链表以NULL结尾,表示无节点。所以在插入或着删除等一些操作要判断是否已经到尾部
		比如linux的list这里是做成循环，然后判断是否和链表头部一致
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
	初试化，将数组全部串连。use指针头为空，free指针头指向数组第0个元素
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
	取得free指针第一个元素
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
	从Use指针中脱离，并且加入Free指针
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
	最快捷方法是将ElementUseHead直接连到ElementFreeHead末尾。当前程序都是默认头部插入
	
	考虑到平常使用不多，Empty仅是测试使用.暂时不重写，保持用Erase
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