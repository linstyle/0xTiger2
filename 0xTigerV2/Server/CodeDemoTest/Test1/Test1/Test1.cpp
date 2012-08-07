// Test1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>
#include "CCommonLibInit.h"
#include "NetAPI.h"
#include "MTASSERT.h"
#include "StackWalker.h"


#include <vector>

using namespace std;

bool volatile g_bQuit=false;


int _tmain(int argc, _TCHAR* argv[])
{
	CCommonLibInit CommonLibInit;

	while(false==g_bQuit)
	{
		g_LogicDriver.Loop();
		
		
		Sleep(100);
	}

	return 0;
}

