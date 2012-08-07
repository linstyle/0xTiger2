// ServerBin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>

#include "CServerBinPublic.h"
#include "Network/CBinServerPlayTCP.h"


/*
  网络线程->接收消息，判断消息种类，即时或延迟
  即时，立刻处理
  延迟，打上时间戳，丢进延迟队列。
  扫描延迟队列
	判断时间是否到达( 服务器收到包的时间+该任务需要延迟的时间+网络延迟时间==当前服务器时间 )，
	并且采取一个快排的原理，把时间接近的提前

*/
//
//全局的退出
volatile bool g_bQuit=false;	

int _tmain(int argc, _TCHAR* argv[])
{
	int nResult;
	WSADATA WsaData;
	nResult = WSAStartup(MAKEWORD(2,2),&WsaData);
	MTVERIFY( 0==nResult );

	CBinServerPlay BinServerPlay;

	BinServerPlay.Init();
	BinServerPlay.Start();

	//
	//Clean
	GetQuitCommand();
	
	printf("Clean start:\n");

	if( WAIT_TIMEOUT==BinServerPlay.BinServerPlayThread.End() )
	{		
		printf("WAIT_TIMEOUT==BinServerThread.End():%d\n", GetLastError());
	}
	
	//BinServerPlay.Release();
	WSACleanup();

	return 0;
}
