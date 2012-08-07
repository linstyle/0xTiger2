/*
	����ģ�鹫��ͷ�ļ�
*/
#pragma once
#pragma comment(lib,"Ws2_32.lib")

#include <Winsock2.h>
#include "0x_Exception.h"
#include "Protocol/ProtocolHead.h"



//
//һЩ���е�SOCKET��Ϣ
class CCommonSocket
{
private:
	/*
		�ĸ�Time,�ֱ��¼���ζ�������ʱ��ʱ�䡣�ṩ���ϲ��һ��ʱ����������������������
		�����������ʹ�÷�Χ�������Щ����Ƶ����΢������绷�������粻�ʺ����£�
		S��C֮��20��ͨ��һ�Σ�����5����һ�Ρ�
	*/
	time_t nFirstRecvTime;
	time_t nSecondRecvTime;

	time_t nFirstSendTime;
	time_t nSecondSendTime;

public:
	int nSocket;
	int nPort;
	unsigned long nIP;		//TCP/IP network byte order
	sockaddr_in Addr;

	CCommonSocket();
	~CCommonSocket();

	/*
		InitSocketXXX
		nNonb = 1;��������ʽ��Ĭ��Ϊ����
	*/
	bool InitSocketTCPS(unsigned long nNonb=0);
	bool InitSocketTCPC(unsigned long nNonb=0);
	
	bool InitSocketUDPS(unsigned long nNonb=0);
	bool InitSocketUDPC(unsigned long nNonb=0);

	/*
		ConnectNonb
		�����������ӷ�ʽ���������׽��ָ�Ϊ��������(windows����ʱ�޷��Ļ��׽��ֵ�ԭ״̬)
	*/
	static int ConnectNonb(int fdNonb, const sockaddr *pConnectAddr, int nConnectAddrSize, int nSec);
	//TCP
	//�ϸ���˵������Ķ�д��Ҫ��ĳ��ȶ�ҪС���׽��ֵ���ͷ���ֵ(SO_RCLOWAT SO_SDLOWAT)
	static int RecvnTCP(int fd, char* pRecvBuffer, int nRecvLen);
	static int SendnTCP(int fd, const char* pSendBuffer, int nSendLen);

	static int RecvnUDP(int fd, char* pRecvBuffer, int nRecvLen, int nRecvFlag, sockaddr* RecvAddr);
	static int SendnUDP(int fd, const char* pSendBuffer, int nSendLen, int nSendFlag, const struct sockaddr* SendAddr);

};

class CPublicProtocolVerify
{
public:

private:	
	int m_nMaxMsgOrderAction;

public:
	CPublicProtocolVerify()
	{
		m_nMaxMsgOrderAction = -1;
	}
	
	void SetVersion1(int nMaxMsgOraderAction);
	bool IsMsgSize(int nInSizeOfMsg, int nWillRecvBytes, int nHasRecvBytes);
	bool IsMsgAction(int nRecvOrderAction);

private:

};