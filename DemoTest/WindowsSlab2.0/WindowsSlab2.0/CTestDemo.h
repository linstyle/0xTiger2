#pragma once
#include <vector>

#include "CThread.h"
#include "CWindowsSlab.h"
//��������

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
	С�ڴ����+����ͷ�
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
	���ڴ����+����ͷ�
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
	ȫ���,��������:
	T��N��
	{
		���N��ȡ�������С��
		���N���ͷŶ���ռ�
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
	int m_nMallocSizeCount;  //m_pMallocSize����ĸ���
	char m_szName[24];
};