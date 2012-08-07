/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                      
    ����˵����  ����ֻ�ǶԷ������ĸ����߳̽���һ��ͳһ�Ĺ���ͷ��䡣�����ǳ����ӵ�����ɾ���ĵȶ�����
				        Ҳ��������������̸߳���ƽ��
    ע�����  �̳�IThread���࣬����ռ���Ҫ��new�ģ������ⲿ����ɾ�����йܸ�ThreadPool
*/

#pragma once

#include <vector>

#include "Singleton.h"
#include "CThread.h"
#include "CTime.h"
#include "MTASSERT.h"

struct THREAD_POOL_OBJECT
{
	THREAD_POOL_OBJECT();

	CThread *pThread;  //�û���thisָ��
	DWORD m_dwStartTime;
	char m_ThreadName[32];
};

typedef std::vector<THREAD_POOL_OBJECT*> ThreadSet_t;

class CThreadPool:public Singleton<CThreadPool>
{
public:
	~CThreadPool();
	/*
		��������:����߳��е���Ϣ
	*/
	void Tracer();


	/*
		��������:ExecutionTarget:����IThread���࣬ �������Զ���ExecutionTarget����
					  ThreadName:������һ�����ֳ���Ϊ16���߳��ַ���
		��������:ִ��һ�������߳�
		��������: 0 �ɹ�
				 -1 ʧ��
	*/
	void ExecuteTask(CThread* ExecutionTarget, const char* ThreadName, int nThreadNumber=1);
private:
	/*
		��������:����һ���߳�
		��������:NULL ʧ��
				 ��ֵ ���ɵ�һ��ThreadCtrl���󣬲����Ѿ���ŵ�m_ThreadSet��
	*/
	THREAD_POOL_OBJECT* StartThread(CThread* ExecutionTarget, const char* ThreadName);

	/*
		��������:�˳������߳�
		��������: 0 �ɹ�
				 -1 ʧ��
	*/
	int Exit();

public:
	

private:
	ThreadSet_t m_ThreadSet;
};


#define g_ThreadPool CThreadPool::getSingleton()
