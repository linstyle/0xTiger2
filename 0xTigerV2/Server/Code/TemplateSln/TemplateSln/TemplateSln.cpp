// 测试工程
// TemplateSln.cpp : 定义控制台应用程序的入口点。
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
	printf("TemplateSln Start\n");
	new CMaster;

	while( false==g_bQuit)
	{
		if( false==g_Master.ServerLoop() )
		{
			printf("goto main_end\n");
			goto main_end;
		}
		Sleep(100);
	}

	
main_end:

	printf("TemplateSln End\n");

	delete CMaster::getSingletonPtr();
	return 0;
}

