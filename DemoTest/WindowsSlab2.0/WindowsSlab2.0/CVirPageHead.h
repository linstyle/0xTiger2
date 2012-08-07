#pragma  once
#include "LinuxList.h"
#include "CWindowsSlabDef.h"
//lindp
//2011.7.17 22:54

/*
	ҳ���������Ϣ����DEBUG������а���
*/

/*
	ҳ��ĵ�ǰ״̬
*/
enum PAGE_STATE
{
	STATE_CACHE_LOCK,						//��ĳ��SLAB����
	STATE_PARTIAL_LOCK,						//��Partial�ڵ���
	STATE_ALL_USER_LOCK,					//ȫ�������û�����
};

class CKmem;
struct VIR_PAGE_HEAD 
{
	void Init(int nFreeObject, CKmem *pKmem, void *pFreeList) 
	{
		m_nFreeObject = nFreeObject;
		m_pFreeList = pFreeList;
		m_pKmem = pKmem;
		m_nState = STATE_CACHE_LOCK;
		m_nBadAlienMagic = name_slab::HEAD_BAD_ALIEN_MAGIC;
		INIT_LIST_HEAD(&m_PageListNode);
	}

	void *m_pFreeList;					 //���е��ڴ�ͷ
	int m_nFreeObject;					 //���е�object����
	CKmem *m_pKmem;						 //��Ӧ��CKmem

	PAGE_STATE m_nState;			 //debug״̬
	unsigned long m_nBadAlienMagic;		 //��ֹת������
	struct list_head m_PageListNode;	 //ҳ��֮�������ڵ�
};
