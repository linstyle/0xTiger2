// WindowsSlab2.0.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>
#include "CWindowsSlab.h"
#include "TestDemo.h"
#include "CTestDemo.h"
#include "CThreadPool.h"
#include <assert.h>

int _tmain(int argc, _TCHAR* argv[])
{
	//name_slab::kmem_init();

	//int *p =(int*) name_slab::kmem_malloc(4);
	//*p=100;

	//printf("%d \n", *p);

	//name_slab::kmem_free(p);

	//name_slab::kemem_traceme();

	/*
		初始化
	*/
	name_slab::kmem_init();

	new CThreadPool;

	SYSTEM_INFO sinf;
	GetSystemInfo(&sinf);
	int nThreadCount =sinf.dwNumberOfProcessors;

//	int nThreadCount =1;

	CTestBigSmallRand *pTest = new CTestBigSmallRand[nThreadCount];


	/*
		执行体
	*/
	for (int i=0; i<nThreadCount; ++i)
	{
		g_ThreadPool.ExecuteTask(pTest+i, pTest->GetInstanceName());
	}

	Sleep(13000);
	for (int i=0; i<nThreadCount; ++i)
	{
		g_ThreadPool.ExecuteTask(pTest+i,  pTest->GetInstanceName());
	}
	
	/*
		回收，输出信息
	*/
	delete CThreadPool::getSingletonPtr();
	delete []pTest;

	name_slab::kemem_traceme();
	return 0;
}

