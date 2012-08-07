/*
	¸ºÔØ·şÎñÆ÷
*/
#include <vld.h>
#include "stdafx.h"

#include "CMaster.h"

volatile bool g_bQuit=false;

int _tmain(int argc, _TCHAR* argv[])
{
	printf("WeightServer Start\n");
	new CMaster;

		
	while( false==g_bQuit)
	{
		g_Master.ServerLoop();
		Sleep(300);
	}

	printf("WeightServer End\n");

	delete CMaster::getSingletonPtr();
	return 0;
}

