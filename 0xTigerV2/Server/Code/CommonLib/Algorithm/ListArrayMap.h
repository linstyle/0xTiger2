/********************************************************************
	created:	2010/07/12
	created:	12:7:2010   14:03
	filename: 	d:\work\TemplateSln\TemplateSln\ListArrayMap.h
	file path:	d:\work\TemplateSln\TemplateSln
	file base:	ListArrayMap
	file ext:	h
	author:		chenfuyuan
	
	purpose:	����Ŀ��ٲ��롢ɾ��

   1 �û���ʹ��ʱ�Զ��������������CKeyId��
   2 ������������ȵ���Reserve()����������洢�ռ�
   3 ������Ԫ�ظ������ó���Reserve()������������Ĵ�С
   4 �Ѿ����ڵĶ��󲻿��ظ�����(����ʧ�ܣ�������ʾ��Ϣ)�������ڵĶ���ɾ��ʱֻ�Ǽ򵥷��أ��޳�����ʾ   
*********************************************************************/
#pragma once
#include <assert.h>
#include <iostream>

using namespace std;

/************************************************************************/
/*
�û��Զ����������̳и���
*/
/************************************************************************/
class CKeyId
{
public:
	CKeyId() 
	{
		m_ID = -1;
	}
	virtual ~CKeyId()
	{
	}

	int m_ID;
};

template<class Key, class Value>
class CListArrayMap
{
public:
	CListArrayMap(void);
	virtual ~CListArrayMap(void);

	/************************************************************************/
	/*���û�������з�װ��CKeyId���û�����ĸ���ָ�룬id��Ϊ���ڿ��ٲ��Ҷ���������
	������ڲ���ʶ���ñ�־Ϊ������Ķ����ڿռ��е�λ��
	*/
	/************************************************************************/
	struct ELEMENT 
	{
		Key first;
		Value second;
		ELEMENT* pPre;
		ELEMENT* pNext;
		int id;
	};

	/************************************************************************/
	/* �������ܣ�ΪCListArrayMap�ڲ��洢����ռ�
       ����˵����nCapacity --- Ԥ���ռ�Ĵ�С(�������)
	   ����ֵ����
	*/
	/************************************************************************/
	bool Reserve(int nCapacity);

	/************************************************************************/
	/* �������ܣ����ݸ����ļ�������ֵ
	   ����˵����cKey --- ��
	   ����ֵ��ֵ
	*/
	/************************************************************************/
	Value Find(Key cKey);

	/************************************************************************/
	/* �������ܣ���ָ���ļ�ֵ���뵽ListArrayMap��
	   ����˵����CKeyId --- ��
	             cValue --- ֵ
	   ����ֵ����
	*/
	/************************************************************************/
	bool Insert(Key cKey, Value cValue);

	/************************************************************************/
	/* �������ܣ���ָ���ļ�ֵ���뵽ListArrayMap��
	   ����˵����CKeyId --- ��
	   ����ֵ����
	*/
	/************************************************************************/
	int Erase(Key ckey);

	/************************************************************************/
	/* �������ܣ�ʣ��ռ�Ĵ�С(�Կ��Բ����Ԫ�ظ���)
	   ����˵������
	   ����ֵ�����Լ��������Ԫ�صĸ���
	*/
	/************************************************************************/
	int GetFreeCount(); 

	/************************************************************************/
	/* �������ܣ��Ѿ�����Ķ������
	   ����˵������
	   ����ֵ���Ѿ�����Ķ������
	*/
	/************************************************************************/
	int GetUsedCount(); 

	void printFreeInfo()
	{
		ELEMENT* p = m_ElementFreeHead.pNext;
		for (;p!=NULL;p=p->pNext)
		{
			cout<<"Free id: "<<p->id<<endl;
		}

	}

	void printUsedInfo()
	{
		ELEMENT* p = m_ElementUsedHead.pNext;
		for (;p!=NULL;p=p->pNext)
		{
			cout<<"Used id: "<<p->id<<endl;
		}

	}

private:
	/************************************************************************/
	/* �������ܣ��ӿ���ռ������л��һ���ռ�
	   ����˵������
	   ����ֵ������ռ�ָ��
	*/
	/************************************************************************/
	ELEMENT* MallocNewElement(); 

	/************************************************************************/
	/* �������ܣ���������뵽ָ����������(���ö�������or����ռ�����)
	   ����˵����pNode --- Ҫ�����Ԫ��
                 pDstListHead --- Ҫ�����Ŀ�������ͷָ��
	   ����ֵ����
	*/
	/************************************************************************/
	void AddNodeToList(ELEMENT* const pNode, ELEMENT* const pDstListHead);

private:
	ELEMENT* m_ElementData;
	ELEMENT m_ElementFreeHead;
	ELEMENT m_ElementUsedHead;
	int m_UsedSum;
	int m_FreeSum;
	int m_Capacity;
};

template<class Key, class Value>
CListArrayMap<Key, Value>::CListArrayMap(void)
{
	m_ElementData = NULL;
	m_ElementFreeHead.pNext = m_ElementFreeHead.pPre = NULL;
	m_ElementUsedHead.pNext = m_ElementUsedHead.pPre = NULL;
	m_UsedSum = 0;
	m_FreeSum = 0;
	m_Capacity = 0;
}

template<class Key, class Value>
CListArrayMap<Key, Value>::~CListArrayMap(void)
{
	if (m_ElementData)
	{
		delete[] m_ElementData;
	}
	m_ElementData = NULL;
	m_UsedSum = 0;
	m_FreeSum = 0;
	m_Capacity = 0;
	m_ElementFreeHead.pNext = m_ElementFreeHead.pPre = NULL;
	m_ElementUsedHead.pNext = m_ElementUsedHead.pPre = NULL;
}

template<class Key, class Value>
bool CListArrayMap<Key, Value>::Reserve(int nCapacity)
{
	assert(nCapacity>0);
	if (nCapacity<=0)
	{
		return false;
	}

	m_Capacity = nCapacity;
	m_ElementData = new ELEMENT[nCapacity];
	m_FreeSum = nCapacity;
	m_UsedSum = 0;

	for (int i=0;i<nCapacity-1;i++)
	{
		m_ElementData[i].pNext = &m_ElementData[i+1];
		m_ElementData[i+1].pPre = &m_ElementData[i];
		m_ElementData[i].id = i;
	}

	m_ElementData[nCapacity-1].pNext = NULL;
	m_ElementData[nCapacity-1].id = nCapacity-1;
	m_ElementFreeHead.pNext = m_ElementData;
	m_ElementUsedHead.pNext = NULL;

	return true;
}

template<class Key, class Value>
typename Value CListArrayMap<Key, Value>::Find(Key cKey)
{
	//assert((cKey->m_ID != -1)&&(NULL != cKey));
	if ((-1 == cKey->m_ID)||(NULL == cKey))
	{
		return NULL;
	}

	return m_ElementData[cKey->m_ID].second;
}

template<class Key, class Value>
bool CListArrayMap<Key, Value>::Insert(Key cKey, Value cValue)
{
//	assert((cKey->m_ID == -1)&&(cKey != NULL));
	if ((-1 != cKey->m_ID)||(NULL == cKey))
	{
		return false;
	}

	ELEMENT* new_elem = MallocNewElement();

	if (new_elem)
	{
		new_elem->first = cKey;
		new_elem->second = cValue;
		cKey->m_ID = new_elem->id;
		return true;
	}
	else
	{
		return false;
	}
}

template<class Key, class Value>
int CListArrayMap<Key, Value>::Erase(Key ckey)
{
	assert((-1 != ckey->m_ID)&&(NULL != ckey));
	if ((-1 == ckey->m_ID)||(NULL == ckey))
	{
		return -1;
	}

	ELEMENT* p = &m_ElementData[ckey->m_ID];
	//ELEMENT* p_next = p->pNext;
	p->pPre->pNext = p->pNext;
	if (p->pNext)
	{
		p->pNext->pPre = p->pPre;
	}

	ckey->m_ID = -1;
	++m_FreeSum;
	--m_UsedSum;
	AddNodeToList(p, &m_ElementFreeHead);

	return 0;
}

template<class Key, class Value>
int CListArrayMap<Key, Value>::GetFreeCount()
{
	return m_FreeSum;
}

template<class Key, class Value>
int CListArrayMap<Key, Value>::GetUsedCount()
{
	return m_UsedSum;
}

template<class Key, class Value>
void CListArrayMap<Key, Value>::AddNodeToList(ELEMENT* pNode, ELEMENT* pDstListHead)
{
	pNode->pNext = pDstListHead->pNext;
	pNode->pPre = pDstListHead;
	if (NULL != pDstListHead->pNext)
	{
		pDstListHead->pNext->pPre = pNode;
	}
	pDstListHead->pNext = pNode;

}

template<class Key, class Value>
typename CListArrayMap<Key, Value>::ELEMENT* CListArrayMap<Key, Value>::MallocNewElement()
{
	//assert(m_ElementFreeHead.pNext != NULL);
	if (NULL == m_ElementFreeHead.pNext)
	{
		return NULL;
	}

	ELEMENT* p = m_ElementFreeHead.pNext;
	m_ElementFreeHead.pNext = p->pNext;
	if (p->pNext)
	{
		p->pNext->pPre = &m_ElementFreeHead;
	}

	AddNodeToList(p, &m_ElementUsedHead);

	--m_FreeSum;
	++m_UsedSum;

	return p;
}
/*

class Key : public CKeyId
{
public:
	Key(int i=0){ this->i = i; }
	virtual ~Key(){}

	void print()
	{
		cout<<"Keyid = "<<m_ID<<endl;
	}

	int i;
};

class Value
{
public:
	Value(){}
	virtual ~Value(){}
	void print()
	{
		cout<<"value ..."<<endl;
	}
	int i;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Key key1 = new Key;
	Value v1 = new Value;
	Key key2 = new Key;
	Value v2 = new Value;
	Key key3 = new Key;
	Value v3 = new Value;
	Key key4 = new Key;
	Value v4 = new Value;
	Key key5 = new Key;
	Value v5 = new Value;
	Key key6 = new Key;
	Value v6 = new Value;
	Key key7 = new Key;
	Value v7 = new Value;
	Key key8 = new Key;
	Value v8 = new Value;
	Key key9 = new Key;
	Value v9 = new Value;
	Key key10 = new Key;
	Value v10 = new Value;

	CListArrayMap<Key, Value> clm;
	clm.Reserve(5);

	clm.Insert(key1, v1);
	clm.Insert(key2, v2);
	clm.Insert(key3, v3);
	clm.Insert(key4, v4);
	clm.Insert(key5, v5);
	clm.Insert(key6, v6);
	clm.Insert(key7, v7);
	clm.Insert(key8, v8);
	clm.Insert(key9, v9);
	clm.Insert(key10, v10);


	clm.printUsedInfo();
	clm.printFreeInfo();
	cout<<"used.."<<clm.GetUsedCount()<<endl;
	cout<<"Free.."<<clm.GetFreeCount()<<endl;


	Value v = clm.Find(key1);
	v->print();
	clm.Erase(key7);
	clm.Erase(key3);
	clm.printUsedInfo();
	clm.printFreeInfo();
	cout<<key3->m_ID<<endl;
	v = clm.Find(key3);
	if (NULL == v)
	{
		//cout<<v->i;
	}
	

	cout<<"used.."<<clm.GetUsedCount()<<endl;
	cout<<"Free.."<<clm.GetFreeCount()<<endl;

	
	return 0;
}


*/