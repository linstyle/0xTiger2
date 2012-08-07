/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/1/31                                                      
    ����˵����  ���С�����������ͷ��ɡ�
				֧�ֶ��߳�
				Put(����)
				const Get(ָ��)

				(k->buffer)->queue, (get do logic)
				(get do put) queue->(buffer->k)
*/

#pragma once

#include <stdio.h>
#include "GlobalType.h"
#include "CLock.h"
#include "LinuxList.h"

namespace name_queue
{
	const int QUEUE_COUNT = 1000;
	/*
		ÿ��������Ĵ�С����λΪ�ֽ� 
	*/
	const int QUEUE_NODE_SIZE = 2048;
};


struct QUEUE_NODE
{
	QUEUE_NODE()
	{
		pBuffer = NULL;
		INIT_LIST_HEAD(&ListNext);
	}
	~QUEUE_NODE()
	{
		delete []pBuffer;
	}

	void Init(int nBufferSize)
	{
		pBuffer = new char[nBufferSize];
		nSize = nBufferSize;
	}

	char *pBuffer;
	int nSize;

	struct list_head ListNext;
};

class CQueue
{
public:
	~CQueue();	

	void Init(int nQueueNodeSize=name_queue::QUEUE_NODE_SIZE, int nQueueCount=name_queue::QUEUE_COUNT);
	void Tracer();

	/*
		���������׽ӿ�:
		��ͳ�����ݿ���
		GetUseNode��ȡһ����Ч������ڵ�,���Ѹýڵ�ŵ����ж�����
		PutUseNode:�ͷ�һ������ڵ㵽��Ч��������
		
		��һЩ��ҪЧ�ʵĵط���ֱ�ӱ�¶ָ����ⲿ,������Ҫ�ֶ��黹ָ��ӵ�
		GetUseNodePtr:ȡһ����Ч������ڵ�ָ��
		GetFreeNodePtr:ȡһ�����е�����ڵ�ָ��
		PutUseNodePtr:�ͷ�һ������ڵ㵽��Ч��������
		PutFreeNodePtr:�ͷ�һ������ڵ㵽���е�������
	*/
	int GetUseNode(char* pBuffer, int nSize);
	bool PutUseNode(const char* pBuffer, int nSize);

	QUEUE_NODE* GetUseNodePtr();
	QUEUE_NODE* GetFreeNodePtr();
	void PutUseNodePtr(QUEUE_NODE* pQueueNode);
	void PutFreeNodePtr(QUEUE_NODE* pQueueNode);

private:
	
	void InitList();

	QUEUE_NODE* _GetUseNode();
	QUEUE_NODE* _GetFreeNode();

	void _PutUseNode(QUEUE_NODE* p);
	void _PutFreeNode(QUEUE_NODE* p);

public:

private:
	int m_nQueueNodeSize;
	int m_nQueueNodeCount;
	QUEUE_NODE *m_pQueueNode;
	list_head m_ListUse;
	list_head m_ListFree;

	CAtom m_nCountListUse;
	CAtom m_nCountListFree;

	CFastLock m_LockListUse;
	CFastLock m_LockListFree;
};

	//CQueue Queue(10, 20);

	//Queue.TracerMe();

	///*
	//	���Ը����Ƿ��
	//*/
	//int i;
	//for(i=0; i<10; ++i)
	//{
	//	char buffer[8];
	//	memset(buffer, 0, 8);
	//	sprintf(buffer, "%d", i);
	//	Queue.PutQueueNode(buffer, strlen(buffer));
	//}
	////Queue.TracerMe();

	//for(i=10; i<25; ++i)
	//{
	//	char buffer[8];
	//	memset(buffer, 0, 8);
	//	sprintf(buffer, "%d", i);
	//	Queue.PutQueueNode(buffer, strlen(buffer));
	//}
	////Queue.TracerMe();

	//for(i=0; i<10; ++i)
	//{
	//	int nSize=8;
	//	char buffer[8];
	//	memset(buffer, 0, 8);
	//	Queue.GetQueueUseNode(buffer, &nSize);
	//}

	//for(i=100; i<105; ++i)
	//{
	//	char buffer[8];
	//	memset(buffer, 0, 8);
	//	sprintf(buffer, "%d", i);
	//	Queue.PutQueueNode(buffer, strlen(buffer));
	//}
	//Queue.TracerMe();
