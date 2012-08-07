/*
	网络模块公共头文件
*/
#pragma once
#pragma comment(lib,"Ws2_32.lib")

#include <Winsock2.h>
#include "0x_Exception.h"
#include "Protocol/ProtocolHead.h"



//
//一些固有的SOCKET信息
class CCommonSocket
{
private:
	/*
		四个Time,分别记录两次动作发生时的时间。提供给上层的一个时间差，可以用来代替心跳包。
		而这个心跳的使用范围是针对那些发送频率稍微快的网络环境。比如不适合以下：
		S和C之间20秒通信一次，心跳5秒检测一次。
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
		nNonb = 1;非阻塞方式，默认为阻塞
	*/
	bool InitSocketTCPS(unsigned long nNonb=0);
	bool InitSocketTCPC(unsigned long nNonb=0);
	
	bool InitSocketUDPS(unsigned long nNonb=0);
	bool InitSocketUDPC(unsigned long nNonb=0);

	/*
		ConnectNonb
		非阻塞的连接方式，主动将套接字改为非阻塞。(windows下暂时无法改回套接字的原状态)
	*/
	static int ConnectNonb(int fdNonb, const sockaddr *pConnectAddr, int nConnectAddrSize, int nSec);
	//TCP
	//严格来说，这里的读写所要求的长度都要小于套接字的最低阀门值(SO_RCLOWAT SO_SDLOWAT)
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