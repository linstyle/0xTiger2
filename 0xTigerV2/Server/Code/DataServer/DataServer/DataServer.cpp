// DataServer.cpp : 定义控制台应用程序的入口点。
//


#include "StdAfx.h"
#include <vld.h>
#include "CMaster.h"
#include "CSlab.h"

#include <vector>

using namespace std;

volatile bool g_bQuit=false;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("DataServer Start\n");
	new CMaster;


	while( false==g_bQuit)
	{
		g_Master.Loop();
		Sleep(100);
	}


	printf("DataServer Stopping.....\n");
	delete CMaster::getSingletonPtr();
	printf("DataServer End\n");
	system("pause");
	return 0;
}

