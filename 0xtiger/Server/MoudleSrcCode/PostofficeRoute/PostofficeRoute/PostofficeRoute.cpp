//�ļ��ṹ��鿴Դ�ļ��е�"file struct with code.txt"
// PostofficeRoute.cpp : �������̨Ӧ�ó������ڵ㡣
/*
	�ͻ���:udp
	���ܿͻ��˵Ķ����ӣ����ܿͻ��ڶ˴�����Ӧ�Ĳ���
	���ظ��ͻ���һ���ܳ�

	�ʾַ�����:tcp
	�����ʾַ���������������û��������ڴ���������������ȵ�
	���ݸ�����������ܳ� 
*/

#include "stdafx.h"
#include <vld.h>

#include "Network/CRoutePlayUDP.h"
#include "Network/CRouteServerTCP.h"

//
//ȫ�ֵ��˳�
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
		�����ǿ��ƿͻ��˵�UDP
	*/
	CRoutePlay RoutePlay;

	RoutePlay.Init(nCPUNumberOf);

	for(i=0; i<nCPUNumberOf; ++i)
	{
		RoutePlay.Start(i);

		//
		//������Ե
		nResult = RoutePlay.pRoutePlayUDPThread[i]._SetThreadIdealProcessor(1<<i);
		MTVERIFY( -1!=nResult );

		nResult = RoutePlay.pRoutePlayUDPThread[i]._ResumeThread();
		MTVERIFY( -1!=nResult );
	}

	/*
		�����ǿ����ʾַ�������TCP
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

