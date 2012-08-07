//#include "TestDemo.h"
//#include <windows.h>
//#include <vector>
//#include <queue>
//
//using namespace std;
//
//int Random(double start, double end)
//{
//	return (int)(start+(end-start)*rand()/(RAND_MAX + 1.0));
//}
//
//struct TKMEM
//{
//	TKMEM(void *_p)
//	{
//		p = _p;
//		b=true;
//	}
//	bool b;
//	void *p;
//};
//
//void test_small()
//{
////����
//	int nMallocCount=10000;		//����Ĵ���
//	int nObjectSize = 4;		//�������Ĵ�С
//	vector<void*> vecMallocAddr;//
//
//	vecMallocAddr.reserve(nMallocCount);
//	
//	DWORD nBeginTime=GetTickCount();
//	printf("begin time:%d\n", nBeginTime);
//	for (int i=0; i<nMallocCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//
//		vecMallocAddr.push_back(p);
//	}
//
//	for (int i=0; i<nMallocCount; i++)
//	{
//		void *p = vecMallocAddr[i];
//		my_free(p);
//	}
//#ifdef TEST_DEMO
//	printf("kmem:<test_small_malloc>spend time:%d\n", GetTickCount()-nBeginTime);
//#else
//	printf("os:<test_small_malloc>spend time:%d\n", GetTickCount()-nBeginTime);
//#endif
//
//	
//}
//
//void test_big()
//{
//	//����
//	int nMallocCount=10000;		//����Ĵ���
//	int nObjectSize = 4096;		//�������Ĵ�С
//	vector<void*> vecMallocAddr;//
//
//	vecMallocAddr.reserve(nMallocCount);
//
//	DWORD nBeginTime=GetTickCount();
//	printf("begin time:%d\n", nBeginTime);
//	for (int i=0; i<nMallocCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//
//		vecMallocAddr.push_back(p);
//	}
//
//	for (int i=0; i<nMallocCount; i++)
//	{
//		void *p = vecMallocAddr[i];
//		my_free(p);
//	}
//
//	
//#ifdef TEST_DEMO
//	printf("kmem:<test_big_malloc>spend time:%d\n", GetTickCount()-nBeginTime);
//#else
//	printf("os:<test_big_malloc>spend time:%d\n", GetTickCount()-nBeginTime);
//#endif
//}
//
//void test_small_rand()
//{
//	//����
//	int nMallocCount=10000;		//����Ĵ���
//	int nFreeCount = nMallocCount/3;	//�ͷŴ�����С�ڷ������(��Ϊ�������ɾ�±�)
//	int nObjectSize = 10;		//�������Ĵ�С
//	vector<TKMEM> vecMallocAddr;//
//
//	vecMallocAddr.reserve(nMallocCount);
//
//	DWORD nBeginTime=GetTickCount();
//	printf("begin time:%d\n", nBeginTime);
//	for (int i=0; i<nMallocCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//		TKMEM t(p);
//
//		vecMallocAddr.push_back(t);
//	}
//
//	for (int i=0; i<nFreeCount; i++)
//	{
//		int nRandIndex = Random(0, nFreeCount);
//		TKMEM t = vecMallocAddr[i];
//		if (false==t.b)
//		{
//			continue;
//		}
//
//		int *p = (int*)t.p;
//		t.b = false;
//		//�ٶ�ȡ�ڴ�һ��
//		memset(p,0,nObjectSize);
//		my_free(p);
//	}
//
//	
//#ifdef TEST_DEMO
//	printf("kmem:<test_small_malloc_rand> spend time:%d\n", GetTickCount()-nBeginTime);
//#else
//	printf("os:<test_small_malloc_rand> spend time:%d\n", GetTickCount()-nBeginTime);
//#endif
//}
//
//void test_big_rand()
//{
//	//����
//	int nMallocCount=100000;		//����Ĵ���
//	int nFreeCount = nMallocCount/3;	//�ͷŴ�����С�ڷ������(��Ϊ�������ɾ�±�)
//	int nObjectSize = 4096;		//�������Ĵ�С
//	vector<void*> vecMallocAddr;//
//
//	vecMallocAddr.reserve(nMallocCount);
//
//	DWORD nBeginTime=GetTickCount();
//	printf("begin time:%d\n", nBeginTime);
//	for (int i=0; i<nMallocCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//
//		vecMallocAddr.push_back(p);
//	}
//
//	for (int i=0; i<nFreeCount; i++)
//	{
//		int nRandIndex = Random(0, nFreeCount);
//		
//		void *p = vecMallocAddr[nRandIndex];
//
//		//�Ⱥ�ĩβ�Ľ�������ֹɾ��ʱ���ģ���ƶ��ڴ�
//		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
//		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
//		vecMallocAddr[nRandIndex] = pSwap;
//
//		//�ٶ�ȡ�ڴ�һ��
//		memset(p,0,nObjectSize);
//
//		//ֻ��pop���һ��
//		vecMallocAddr.pop_back();
//		my_free(p);
//	}
//#ifdef TEST_DEMO
//	printf("kmem:<test_big_malloc_rand> spend time:%d\n", GetTickCount()-nBeginTime);
//#else
//	printf("os:<test_big_malloc_rand> spend time:%d\n", GetTickCount()-nBeginTime);
//#endif
//	
//}
//
//
///////////////////////////////////////////
//
////�ĸ�������
////�������N�����ڴ棬�������N��С�ڴ棻
////����ͷ�N�����ڴ棬�������N��С�ڴ�
////����һ�������������������
//void _sub_bm_malloc_big(vector<void*>& vecMBig, int nCount)
//{
//	int nObjectSize = 4000; //4kb
//
//	for (int i=0; i<nCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//
//		vecMBig.push_back(p);
//	}
//}
//
//void _sub_bm_malloc_small(vector<void*>& vecMSmall, int nCount)
//{
//	int nObjectSize = 8; //8byte
//
//	for (int i=0; i<nCount; i++)
//	{
//		int *p =(int*) my_malloc(nObjectSize);
//		memset(p,0,nObjectSize);
//
//		vecMSmall.push_back(p);
//	}
//}
//
//void _sub_bm_free_big(vector<void*>& vecFBig, int nCount)
//{
//	int nObjectSize = 8; //8byte
//
//	for (int i=0; i<nCount; i++)
//	{
//		int nRandIndex = Random(0, vecFBig.size());
//		
//		int *p = (int*)vecFBig[nRandIndex];
//		my_free(p);
//
//		vecFBig.erase(vecFBig.begin()+nRandIndex);
//	}
//}
//
//void _sub_bm_free_small(vector<void*>& vecFSmall, int nCount)
//{
//
//}
//
//void _sub_test_bm_rand(vector<void*>& vecMBig, vector<void*>& vecMSmall, 
//							  vector<void*>& vecFBig, vector<void*>& vecFSmall)
//{
//	//�������
//	const int nMaxMallocBigCount = 100000;  //������ڴ����	
//	const int nMaxMallocSmallCount = 100000;  //����С�ڴ����
//	const int nMaxFreeBigCount = 100000;  //�ͷŴ��ڴ����
//	const int nMaxFreeSmallCount = 100000;  //�ͷ�С�ڴ����
//
//
//	//rand, malloc, big
//	
//
//	//rand, malloc, small
//	int nMallocSmallCount;
//
//	//rand, free, big
//
//
//	//rand, free, small
//}
//
//void test_big_small_rand()
//{
//	//���̣�
//	//t=�����ȥN��������ͷż���N��
//	//�ظ��������S��
//
//	//����
//
//}
//
