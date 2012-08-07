// ClientPlay.cpp : Defines the entry point for the console application.
//

/*
									客户端属于测试代码
*/

#include "stdafx.h"
#include <vld.h>

#include "CClientPlayPublic.h"
#include "Network/CPlayServerTCP.h"
#include "Network/CPlayRouteUDP.h"

//
//全局的退出
volatile bool g_bQuit=false;				


int _tmain(int argc, _TCHAR* argv[])
{	
	bool bResult;
	int i, nResult;
	
	WSADATA WsaData;
	nResult = WSAStartup(MAKEWORD(2,2),&WsaData);
	MTVERIFY( 0==nResult );

	//
	//UDP，登陆信息获取线程
	CPlayRoute PlayRoute;

	PlayRoute.Init();
	PlayRoute.Start();

	//
	//TCP正式线程
	CPlayServer PlayServer;

	PlayServer.Init();
	PlayServer.Start();

	//
	//是否取到登陆信息,如果成功，唤醒TCP
	while(g_bQuit!=true)
	{
		if( true==PlayRoute.PlayRouteUDP.GetbGetLoginInfo() )
		{
			PlayServer.PlayServerTCP.ReadFromContent( PlayRoute.PlayRouteUDP.GetLoginInfo() );
			nResult = PlayServer.PlayServerTCPThread.Resume();
			MTVERIFY( -1!=nResult );

			break;
		}

		Sleep(500);
	}

	//
	//Clean
	GetQuitCommand();
	printf("Clean start:\n");	

	if( WAIT_TIMEOUT!=PlayServer.PlayServerTCPThread.End() )
	{
		printf("WAIT_TIMEOUT==PlayServerTCPThread.End():%d\n", GetLastError());		
	}

	if( WAIT_TIMEOUT!=PlayRoute.PlayRouteUDPThread.End() )
	{
		printf("WAIT_TIMEOUT==PlayRouteUDPThread.End():%d\n", GetLastError());		
	}

	WSACleanup();
	return 0;
}

