// Hello.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <map>
#include "CMyStackWalker.h"
#include "CVirtualCell.h"
using namespace std;


int _GetPassWeekendDays(int nStartsWDay, int nDistanceDays)
{
	int nSumWeekendDays=0;
	for (int i=nStartsWDay; i<=(nStartsWDay+nDistanceDays)-1; i++)
	{
		int nVerifyDays = i % 7;
		if (0==nVerifyDays || 6==nVerifyDays)
		{
			nSumWeekendDays++;
		}
	}

	return nSumWeekendDays;
}

/*
	GetPassWeekendDays
	@获取经过的周六，周日天数
	@nStartsWDay 从星期天开始，[0,6], 跟C结构的 struct tm{} tm_wday一致
	@nDistanceDays 经过的天数
*/
int GetPassWeekendDays(int nStartsWDay, int nDistanceDays)
{
	//一周7天，先算出7的倍数
	int nPassWeek = nDistanceDays / 7;

	//余几天
	int nRemainDays = nDistanceDays % 7;

	//起始点不算
	nStartsWDay = (nStartsWDay+1) % 7;

	//*2 周六、周日有两天
	return _GetPassWeekendDays(nStartsWDay, nRemainDays) + nPassWeek*2;
}





int _tmain(int argc, _TCHAR* argv[])
{

	CVirtualCell VirtualCell;
	
	VirtualCell.Init(100,100,20);
	VirtualCell.TraceMe();

	printf("=============\n\n\n");

	vector<int> vecBlock;

	

	for (int i=0; i<5; i++)
	{
		VirtualCell.GetAroundBlockByLevel(45, 20, vecBlock, i);

		for (int j=0; j<vecBlock.size(); ++j)
		{
			printf("%5d", vecBlock[j]);
		}

		printf("\n\n\n  levl:%d=============", i);
		vecBlock.clear();
	}



	//int TestData[][2]={
	//	{5,1},{2,2},{2,4},
	//	{3,512},{3,5},{6,3},
	//	{0,1000}
	//				  };

	//for (int i=0; i<sizeof(TestData)/sizeof(*TestData); i++)
	//{
	//	int nStartsWDay = TestData[i][0];
	//	int nDistanceDays = TestData[i][1];
	//	printf("nStartsWDay:周%d, nDistanceDays:%d, %d\n", 
	//		nStartsWDay, nDistanceDays, GetPassWeekendDays(nStartsWDay, nDistanceDays));
	//}

	//printf("============\n");
	//for (int i=0; i<sizeof(TestData)/sizeof(*TestData); i++)
	//{
	//	int nStartsWDay = TestData[i][0];
	//	int nDistanceDays = TestData[i][1];
	//	printf("nStartsWDay:周%d, nDistanceDays:%d, %d\n", 
	//		nStartsWDay, nDistanceDays, _GetPassWeekendDays(nStartsWDay, nDistanceDays));
	//}
	


	return 0;
}
/*
00411A6B  mov         eax,dword ptr [i3] 
00411A6E  cdq              
00411A6F  mov         dword ptr [i2],eax 
00411A72  mov         dword ptr [ebp-20h],edx 

long long i2=i1;
00411A6B  mov         eax,dword ptr [i1] 
00411A6E  xor         ecx,ecx 
00411A70  mov         dword ptr [i2],eax 
00411A73  mov         dword ptr [ebp-20h],ecx 

*/

