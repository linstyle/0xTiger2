// ServerBin.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>

#include "CServerBinPublic.h"
#include "Network/CBinServerPlayTCP.h"


/*
  �����߳�->������Ϣ���ж���Ϣ���࣬��ʱ���ӳ�
  ��ʱ�����̴���
  �ӳ٣�����ʱ����������ӳٶ��С�
  ɨ���ӳٶ���
	�ж�ʱ���Ƿ񵽴�( �������յ�����ʱ��+��������Ҫ�ӳٵ�ʱ��+�����ӳ�ʱ��==��ǰ������ʱ�� )��
	���Ҳ�ȡһ�����ŵ�ԭ����ʱ��ӽ�����ǰ

*/
//
//ȫ�ֵ��˳�
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
