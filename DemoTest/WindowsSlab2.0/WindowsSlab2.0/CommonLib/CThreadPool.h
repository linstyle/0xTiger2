/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                      
    ����˵����  ����ֻ�ǶԷ������ĸ����߳̽���һ��ͳһ�Ĺ���ͷ��䡣�����ǳ����ӵ�����ɾ���ĵȶ�����
				        Ҳ��������������̸߳���ƽ��.
	ע�⣺pIThread���ⲿ��������
*/

#pragma once

#include <vector>

#include "Singleton.h"
#include "CThread.h"
#include "CTime.h"
#include "MTVERIFY.h"

struct ThreadCtrl
{
	ThreadCtrl();
	~ThreadCtrl();
	/*
		pIThread   :���û�����
		Thread	   :�ڲ�ά�����߳���������
		ThreadName :�߳��ַ�����ʶ��������־�����ӡ
	*/
	IThread *pIThread;
	CThread Thread;
	char ThreadName[20];
};

typedef std::vector<ThreadCtrl*> ThreadSet_t;

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
	*/
	bool ExecuteTask(IThread * ExecutionTarget, const char* ThreadName);

private:
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


/*
	ʹ�÷���


class T1:public IThread
{
public:
	T1()
	{
		m_bRun = true;
	}

	virtual S32 Run()
	{
		while(m_bRun)
		{
			printf("T1 run.....\n");
			UserHeartBeat();
			Sleep(1000);
		}
		return 0;
	}
	virtual S32 Exit()
	{
		m_bRun = false;		
		printf("T1 Exit.......\n");
		return 0;
	}

public:
	volatile bool m_bRun;
};


class T2:public IThread
{
public:
	T2()
	{
		m_bRun = true;
	}

	virtual S32 Run()
	{
		while(m_bRun)
		{
			printf("T2 run.....\n");
			UserHeartBeat();
			Sleep(1000);
		}
		return 0;
	}
	virtual S32 Exit()
	{
		m_bRun = false;
		printf("T2 Exit.......\n");
		return 0;
	}

public:
	volatile bool m_bRun;
};


int _tmain(int argc, _TCHAR* argv[])
{
	T1 t1;
	T2 t2;

	g_ThreadPool.ExecuteTask(&t1, "t1");
	g_ThreadPool.ExecuteTask(&t2, "t2");

	g_ThreadPool.Tracer();

	g_ThreadPool.Tracer();
	g_ThreadPool.Exit();

	return 0;
}

*/