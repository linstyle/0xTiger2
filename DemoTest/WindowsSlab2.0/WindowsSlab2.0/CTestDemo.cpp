#include "..\StdAfx.h"
#include "CTestDemo.h"

int Random(double start, double end)
{
	return (int)(start+(end-start)*rand()/(RAND_MAX + 1.0));
}

/*
	С�ڴ����+����ͷ�
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

		//�Ⱥ�ĩβ�Ľ�������ֹɾ��ʱ���ģ���ƶ��ڴ�
		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
		vecMallocAddr[nRandIndex] = pSwap;

		//�ٶ�ȡ�ڴ�һ��
		memset(p,0,m_nObjectSize);

		//ֻ��pop���һ��
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
	���ڴ����+����ͷ�
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

		//�Ⱥ�ĩβ�Ľ�������ֹɾ��ʱ���ģ���ƶ��ڴ�
		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
		vecMallocAddr[nRandIndex] = pSwap;

		//�ٶ�ȡ�ڴ�һ��
		memset(p,0,m_nObjectSize);

		//ֻ��pop���һ��
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
	ȫ���,��������:
	T��N��
	{
		���N��ȡ�������С,���ж����СҲ�������
		���N���ͷŶ���ռ�
	}
*/
CTestBigSmallRand::CTestBigSmallRand()
{
	m_nSumCount = 100;
	m_nMallocCount = 3000;
	memset(m_szName, 0, sizeof(m_szName));
	strcpy(m_szName, "CTestBigSmallRand");

	//��С����kmem֧�ֵĻ�ȡ
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
		//�����һ��Ҫ����Ĵ�С����kmem֧�ֵ���������
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

		//�Ⱥ�ĩβ�Ľ�������ֹɾ��ʱ���ģ���ƶ��ڴ�
		void *pSwap = vec[vec.size()-1];
		vec[vec.size()-1]=vec[nRandIndex];
		vec[nRandIndex] = pSwap;

		//ֻ��pop���һ��
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

