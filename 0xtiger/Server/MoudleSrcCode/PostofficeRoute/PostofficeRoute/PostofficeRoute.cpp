//文件结构请查看源文件中的"file struct with code.txt"
// PostofficeRoute.cpp : 定义控制台应用程序的入口点。
/*
	客户端:udp
	接受客户端的短连接，接受客户口端传递相应的参数
	返回给客户端一个密匙

	邮局服务器:tcp
	监视邮局服务器负载情况。用户数量，内存情况，场景人数等等
	根据负载情况产生密匙 
*/

#include "stdafx.h"
#include <vld.h>

#include "Network/CRoutePlayUDP.h"
#include "Network/CRouteServerTCP.h"

//
//全局的退出
bool g_bQuit=false;				


int _tmain(int argc, _TCHAR* argv[])
{	
	bool bResult;
	int i, nResult;
	
	WSADATA WsaData;
	nResult = WSAStartup(MAKEWORD(2,2),&WsaData);
	MTVERIFY( 0==nResult );

	int nCPUNumberOf;
	nCPUNumberOf = GetCPUNumberOf();

	/*
		这里是控制客户端的UDP
	*/
	CRoutePlay RoutePlay;

	RoutePlay.Init(nCPUNumberOf);

	for(i=0; i<nCPUNumberOf; ++i)
	{
		RoutePlay.Start(i);

		//
		//设置亲缘
		nResult = RoutePlay.pRoutePlayUDPThread[i]._SetThreadIdealProcessor(1<<i);
		MTVERIFY( -1!=nResult );

		nResult = RoutePlay.pRoutePlayUDPThread[i]._ResumeThread();
		MTVERIFY( -1!=nResult );
	}

	/*
		这里是控制邮局服务器的TCP
	*/
	CRouteServer RouteServer;

	RouteServer.Init();
	RouteServer.Start();
	
	//
	//Clean
	GetQuitCommand();

	printf("Clean start:\n");	

	for(i=0; i<nCPUNumberOf; ++i)
	{
		if( WAIT_TIMEOUT!=RoutePlay.pRoutePlayUDPThread[i].End() )
		{
			printf("WAIT_TIMEOUT==RoutePlay.pRoutePlayUDPThread[%d].End():%d\n", GetLastError());			
		}		
	}

	if( WAIT_TIMEOUT!=RouteServer.RouteServerTCPThread.End() )
	{
		printf("WAIT_TIMEOUT==RouteServer.RouteServerTCPThread.End():%d\n", GetLastError());		
	}	

	WSACleanup();

	return 0;
}

