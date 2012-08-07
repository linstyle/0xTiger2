#include "..\StdAfx.h"
#include "CTestDemo.h"

int Random(double start, double end)
{
	return (int)(start+(end-start)*rand()/(RAND_MAX + 1.0));
}

/*
	小内存分配+随机释放
*/
CTestSmallRand::CTestSmallRand()
{
	m_nMallocCount = 300000;
	m_nObjectSize = 4;
	memset(m_szName, 0, sizeof(m_szName));
	strcpy(m_szName, "CTestSmallRand");
}

int CTestSmallRand::Run()
{
	vector<void*> vecMallocAddr;//

	vecMallocAddr.reserve(m_nMallocCount);

	for (int i=0; i<m_nMallocCount; i++)
	{
		int *p =(int*) my_malloc(m_nObjectSize);
		memset(p,0,m_nObjectSize);

		vecMallocAddr.push_back(p);
	}

	for (int i=0; i<vecMallocAddr.size(); i++) 
	{
		int nRandIndex = Random(0, vecMallocAddr.size());
		void *p = vecMallocAddr[nRandIndex];

		//先和末尾的交换，防止删除时大规模的移动内存
		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
		vecMallocAddr[nRandIndex] = pSwap;

		//再读取内存一次
		memset(p,0,m_nObjectSize);

		//只需pop最后一个
		vecMallocAddr.pop_back();
		my_free(p);
	}
	return 0;
}

int CTestSmallRand::Exit()
{
	printf("CTestSmallRand::Exit()\n");
	return 0;
}

char* CTestSmallRand::GetInstanceName()
{
	return m_szName;
}

/*
	大内存分配+随机释放
*/
CTestBigRand::CTestBigRand()
{
	m_nMallocCount = 100000;
	m_nObjectSize = 4096;
	memset(m_szName, 0, sizeof(m_szName));
	strcpy(m_szName, "CTestBigRand");
}

int CTestBigRand::Run()
{
	vector<void*> vecMallocAddr;//

	vecMallocAddr.reserve(m_nMallocCount);

	for (int i=0; i<m_nMallocCount; i++)
	{
		int *p =(int*) my_malloc(m_nObjectSize);
		memset(p,0,m_nObjectSize);

		vecMallocAddr.push_back(p);
	}

	for (int i=0; i<vecMallocAddr.size(); i++) 
	{
		int nRandIndex = Random(0, vecMallocAddr.size());
		void *p = vecMallocAddr[nRandIndex];

		//先和末尾的交换，防止删除时大规模的移动内存
		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
		vecMallocAddr[nRandIndex] = pSwap;

		//再读取内存一次
		memset(p,0,m_nObjectSize);

		//只需pop最后一个
		vecMallocAddr.pop_back();
		my_free(p);
	}

	return 0;
}

int CTestBigRand::Exit()
{
	printf("CTestBigRand::Exit()\n");
	return 0;
}

char* CTestBigRand::GetInstanceName()
{
	return m_szName;
}


/*
	全随机,流程如下:
	T的N次
	{
		随机N次取出对象大小,其中对象大小也是随机；
		随机N次释放对象空间
	}
*/
CTestBigSmallRand::CTestBigSmallRand()
{
	m_nSumCount = 100;
	m_nMallocCount = 3000;
	memset(m_szName, 0, sizeof(m_szName));
	strcpy(m_szName, "CTestBigSmallRand");

	//大小，从kmem支持的获取
	m_nMallocSizeCount = sizeof(name_slab::KmemMallocByte)/sizeof(*name_slab::KmemMallocByte);
	m_pMallocSize = new int[m_nMallocSizeCount];
	memcpy(m_pMallocSize, name_slab::KmemMallocByte, sizeof(name_slab::KmemMallocByte));
}

CTestBigSmallRand::~CTestBigSmallRand()
{
	delete m_pMallocSize;
}

void CTestBigSmallRand::SubMallocFn(vector_t& vec)
{
	int nMallocCount = Random(0, m_nMallocCount);

	for (int i=0; i<nMallocCount; ++i)
	{
		//随机出一个要申请的大小，从kmem支持的里面申请
		int nMallocSizeIndex = Random(0, m_nMallocSizeCount);
		int nMallocSize = m_pMallocSize[nMallocSizeIndex];

		int *p =(int*) my_malloc(nMallocSize);
		memset(p,0,nMallocSize);

		vec.push_back(p);		
	}
}

void CTestBigSmallRand::SubReleaseFn(vector_t& vec)
{
	int nMallocCount = vec.size();
	for (int i=0; i<nMallocCount/2; ++i)
	{
		int nRandIndex = Random(0, vec.size());
		void *p = vec[nRandIndex];

		//先和末尾的交换，防止删除时大规模的移动内存
		void *pSwap = vec[vec.size()-1];
		vec[vec.size()-1]=vec[nRandIndex];
		vec[nRandIndex] = pSwap;

		//只需pop最后一个
		vec.pop_back();
		my_free(p);
	}
}


int CTestBigSmallRand::Run()
{
	vector_t vecAddr;//

	vecAddr.reserve(m_nSumCount);

	for (int i=0; i<m_nSumCount; ++i)
	{
		SubMallocFn(vecAddr);
		SubReleaseFn(vecAddr);
	}
	return 0;
}

int CTestBigSmallRand::Exit()
{
	printf("CTestBigSmallRand::Exit()\n");
	return 0;
}

char* CTestBigSmallRand::GetInstanceName()
{
	return m_szName;
}

