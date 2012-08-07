#pragma once
#include <vector>

#include "CThread.h"
#include "CWindowsSlab.h"
//测试用例

using namespace std;



#define  TEST_DEMO

#ifdef TEST_DEMO
#define  my_malloc(p) name_slab::kmem_malloc(p)
#define  my_free(p) name_slab::kmem_free(p)
#else
#define  my_malloc(p) malloc(p)
#define  my_free(p) free(p)
#endif


int Random(double start, double end);


/*
	小内存分配+随机释放
*/
class CTestSmallRand:public IThread
{
public:
	CTestSmallRand();

	virtual int Run();	
	virtual int Exit();

	char* GetInstanceName();
private:

public:
private:
	int m_nMallocCount;
	int m_nObjectSize;
	char m_szName[24];
}; 

/*
	大内存分配+随机释放
*/
class CTestBigRand:public IThread
{
public:
	CTestBigRand();

	virtual int Run();	
	virtual int Exit();

	char* GetInstanceName();
private:

public:
private:
	int m_nMallocCount;
	int m_nObjectSize;
	char m_szName[24];
}; 

/*
	全随机,流程如下:
	T的N次
	{
		随机N次取出对象大小；
		随机N次释放对象空间
	}
*/
class CTestBigSmallRand:public IThread
{
public:
	CTestBigSmallRand();
	~CTestBigSmallRand();

	virtual int Run();	
	virtual int Exit();

	char* GetInstanceName();
private:
	typedef vector<void*> vector_t;

	void SubMallocFn(vector_t& vec);
	void SubReleaseFn(vector_t& vec);
	

public:
private:
	int m_nSumCount;
	int m_nMallocCount;
	
	int *m_pMallocSize;
	int m_nMallocSizeCount;  //m_pMallocSize分配的个数
	char m_szName[24];
};