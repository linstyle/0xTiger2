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
////参数
//	int nMallocCount=10000;		//分配的次数
//	int nObjectSize = 4;		//分配对象的大小
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
//	//参数
//	int nMallocCount=10000;		//分配的次数
//	int nObjectSize = 4096;		//分配对象的大小
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
//	//参数
//	int nMallocCount=10000;		//分配的次数
//	int nFreeCount = nMallocCount/3;	//释放次数，小于分配次数(因为是随机不删下标)
//	int nObjectSize = 10;		//分配对象的大小
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
//		//再读取内存一次
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
//	//参数
//	int nMallocCount=100000;		//分配的次数
//	int nFreeCount = nMallocCount/3;	//释放次数，小于分配次数(因为是随机不删下标)
//	int nObjectSize = 4096;		//分配对象的大小
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
//		//先和末尾的交换，防止删除时大规模的移动内存
//		void *pSwap = vecMallocAddr[vecMallocAddr.size()-1];
//		vecMallocAddr[vecMallocAddr.size()-1]=vecMallocAddr[nRandIndex];
//		vecMallocAddr[nRandIndex] = pSwap;
//
//		//再读取内存一次
//		memset(p,0,nObjectSize);
//
//		//只需pop最后一个
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
////四个函数，
////随机分配N个大内存，随机分配N个小内存；
////随机释放N个大内存，随机分配N个小内存
////再有一个管理函数随机调用它们
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
//	//分配参数
//	const int nMaxMallocBigCount = 100000;  //分配大内存次数	
//	const int nMaxMallocSmallCount = 100000;  //分配小内存次数
//	const int nMaxFreeBigCount = 100000;  //释放大内存次数
//	const int nMaxFreeSmallCount = 100000;  //释放小内存次数
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
//	//流程：
//	//t=分配出去N个，随机释放几个N个
//	//重复这个流程S次
//
//	//参数
//
//}
//
