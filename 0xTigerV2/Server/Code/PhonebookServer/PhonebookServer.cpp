/*
	关系服务器
*/
#include "stdafx.h"
#include <vld.h>

#include "CMaster.h"

volatile bool g_bQuit=false;


int _tmain(int argc, _TCHAR* argv[])
{
	printf("PhonebookServer Start\n");
	new CMaster;

		
	while( false==g_bQuit)
	{
		g_Master.ServerLoop();
		Sleep(100);
	}


	printf("PhonebookServerStopping.....\n");
	delete CMaster::getSingletonPtr();
	printf("PhonebookServer End\n");
	system("pause");
	return 0;
}

/*

*/