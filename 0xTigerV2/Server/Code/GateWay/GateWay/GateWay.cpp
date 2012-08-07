// GateWay.cpp : 定义控制台应用程序的入口点。
//
/*
	1）数据压缩，解压
	2）数据正确性校验
	
	1）维护一个拓扑图，根据一些信息（客户端包自带、gateway上维护的）知道
		 客户端的包要发往那个逻辑服务器里

		  客户端1->逻辑服务器
		  客户端2->逻辑服务器
		  客户端3->逻辑服务器
*/

#include "StdAfx.h"
#include <vld.h>
#include "CMaster.h"
#include "CSlab.h"

#include <vector>

using namespace std;

volatile bool g_bQuit=false;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("GateWayServer Start\n");
	new CMaster;


	while( false==g_bQuit)
	{
		g_Master.Loop();
		Sleep(100);
	}


	printf("GateWayServer Stopping.....\n");
	delete CMaster::getSingletonPtr();
	printf("GateWayServer End\n");
	system("pause");
	return 0;
}

