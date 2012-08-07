// PostofficeServer.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include <vld.h>
#include "stdafx.h"
#include "CServerPublic.h"
#include "Network/CServerBinPlayTCP.h"
#include "Network/CServerRouteTCP.h"

//
//ȫ�ֵ��˳�
volatile bool g_bQuit=false;	

int _tmain(int argc, _TCHAR* argv[])
{	
	int i, nResult;
	
	WSADATA WsaData;
	nResult = WSAStartup(MAKEWORD(2,2),&WsaData);
	MTVERIFY( 0==nResult );

	/*
		�����ǿ��ƺ��ʾ�·�ɵĸ����߳�
	*/
	CServerRoute ServerRoute;

	ServerRoute.Init();
	ServerRoute.Start();


	/*
		�����ǿ�����ɶ˿ڵ�
	*/
	int nCPUNumberOf = GetCPUNumberOf()*2;

	CServerBinPlay ServerBinPlay;
	ServerBinPlay.Init( nCPUNumberOf );

	for(i=0; i<nCPUNumberOf; ++i)
	{
		ServerBinPlay.Start(i);
	}

	ServerBinPlay.StartAccept();

	//
	//Clean
	GetQuitCommand();
	printf("Clean start:\n");

	if( WAIT_TIMEOUT==ServerRoute.ServerRouteThread.End() )
	{
		printf("WAIT_TIMEOUT==ServerRouteThread.End():%d\n", GetLastError());		
	}

	if( WAIT_TIMEOUT==ServerBinPlay.ServerBinPlayThreadAccept.End() )
	{
		printf("WAIT_TIMEOUT==ServerBinPlayAccept.End():%d\n", GetLastError());		
	}

	for(i=0; i<nCPUNumberOf; ++i)
	{
		if( WAIT_TIMEOUT==ServerBinPlay.pServerBinPlayThread[i].End() )
		{
			printf("WAIT_TIMEOUT==ServerBinPlay.pServerBinPlayThread.End():%d\n", GetLastError());			
		}
	}

	WSACleanup();
        
	return 0;
}

