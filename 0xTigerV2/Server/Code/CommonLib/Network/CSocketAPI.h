/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                         
    ����˵����  �׽���api�ĳ�������
*/

#pragma once
#pragma comment(lib,"Ws2_32.lib")

#include <Winsock2.h>
#include <stdio.h>
#include "MTASSERT.h"

//#define printf(level) printf(level##",%s::%s:%d, Err:%d\n", __FILE__, __FUNCTION__, __LINE__, WSAGetLastError())

class CSocketAPI
{
public:

	/*
		��������: ��ʼ����Ӧ��Э���
	*/
	static bool InitSocketTCPS(SOCKET &Socket, ULONG nIP, USHORT nPort, ULONG nNonb=0);
	static bool InitSocketTCPC(SOCKET &Socket, ULONG nIP, USHORT nPort, ULONG nNonb=0);
	
	static bool InitSocketUDPS(SOCKET &Socket, ULONG nIP, USHORT nPort, ULONG nNonb=0);
	static bool InitSocketUDPC(SOCKET &Socket, ULONG nIP, USHORT nPort, ULONG nNonb=0);

	/*
		��������: ��װ�׽��ֵĶ���
		����ֵ:   -1 ʧ��
				  >=0 �ɹ��������ǽ���/���͵��ֽ���
	*/
	static int ConnectNonb(int fdNonb, const sockaddr *pConnectAddr, int nConnectAddrSize, int nSec);
	static int RecvnTCP(SOCKET fd, char* pRecvBuffer, int nRecvLen);
	static int SendnTCP(SOCKET fd, const char* pSendBuffer, int nSendLen);

	static int RecvnUDP(SOCKET fd, char* pRecvBuffer, int nRecvLen, int nRecvFlag, sockaddr* FromAddr);
	static int SendnUDP(SOCKET fd, const char* pSendBuffer, int nSendLen, int nSendFlag, const struct sockaddr* SendAddr);

private:

public:



private:

};