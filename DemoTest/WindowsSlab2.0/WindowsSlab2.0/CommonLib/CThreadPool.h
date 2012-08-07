/*  作者：		林东平                                                              
	创建时间：	2010/06/21                                                      
    功能说明：  该类只是对服务器的各个线程进行一个统一的管理和分配。不做非常复杂的增、删、改等动作，
				        也不做各个任务的线程负载平衡.
	注意：pIThread的外部生命周期
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
		pIThread   :由用户传递
		Thread	   :内部维护的线程周期数据
		ThreadName :线程字符串标识，方便日志输出打印
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
		函数功能:输出线程中的信息
	*/
	void Tracer();


	/*
		函数参数:ExecutionTarget:派生IThread的类， 程序类自动对ExecutionTarget回收
					  ThreadName:允许传递一个名字长度为16的线程字符串
		函数功能:执行一个任务线程
	*/
	bool ExecuteTask(IThread * ExecutionTarget, const char* ThreadName);

private:
	/*
		函数功能:退出所有线程
		函数返回: 0 成功
				 -1 失败
	*/
	int Exit();

public:
	

private:
	ThreadSet_t m_ThreadSet;
};


#define g_ThreadPool CThreadPool::getSingleton()


/*
	使用范例


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