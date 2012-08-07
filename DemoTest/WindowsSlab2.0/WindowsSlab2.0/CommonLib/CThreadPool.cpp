#include "..\StdAfx.h"
#include "CThreadPool.h"
#include <process.h>
#include <assert.h>


initialiseSingleton(CThreadPool);
ThreadCtrl::ThreadCtrl()
{
	memset(ThreadName, 0, sizeof(ThreadName));
}

ThreadCtrl::~ThreadCtrl()
{

}

static unsigned int WINAPI ThreadProc(void* param)
{
	int nResult;
	ThreadCtrl *pTC = (ThreadCtrl *)param;

	try
	{
		nResult = pTC->pIThread->Run();
	}
	catch(...)
	{
		printf("%s:ThreadProc try oop \n", pTC->ThreadName);
	}

	return 0;
}

CThreadPool::~CThreadPool()
{
	Exit();
}

void CThreadPool::Tracer()
{
	printf("/***ThreadPool***/\n");
	printf("Thread Count:%d\n", m_ThreadSet.size());

	ThreadSet_t::iterator itr;
	for(itr=m_ThreadSet.begin(); itr!=m_ThreadSet.end(); itr++)
	{
		printf("Thread name:%s	", (*itr)->ThreadName);
		printf("Thread id:%d	", (*itr)->Thread.m_uThread);
		printf("Thread active:%d", (*itr)->pIThread->UserIsActivity());
		printf("\n");
	}

	printf("\n");
}

bool CThreadPool::ExecuteTask(IThread * ExecutionTarget, const char* ThreadName)
{
	ThreadCtrl *pTC= new ThreadCtrl;

	pTC->pIThread = ExecutionTarget;
	strncpy(pTC->ThreadName, ThreadName, 16);
	pTC->Thread.m_dwStartTime = CTime::GetMilli();

	pTC->Thread.m_hThread = (HANDLE)_beginthreadex(NULL, 0, ThreadProc, pTC, 0, &pTC->Thread.m_uThread);	
	MTVERIFY( 0!= pTC->Thread.m_hThread);

	m_ThreadSet.push_back(pTC);

	return true;
}

int CThreadPool::Exit()
{
	ThreadSet_t::iterator itr;

	for(itr=m_ThreadSet.begin(); itr!=m_ThreadSet.end(); itr++)
	{
		(*itr)->pIThread->Exit();
		(*itr)->Thread.Join();
		
		printf("Thread %s Quit, Spend Time:%d(ms)\n", (*itr)->ThreadName, CTime::GetMilli()-(*itr)->Thread.m_dwStartTime);
		delete (*itr);  //delete for ThreadCtrl
	}

	return 0;
}

