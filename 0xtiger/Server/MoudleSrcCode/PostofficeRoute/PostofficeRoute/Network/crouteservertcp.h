/*
很简单的网络层，实现TCP(Select)和一些协议正确的检测。
协议的具体由CWorldPlay调度
*/
#pragma once
#include "CNetworkPublicSelect.h"

#include "../stdafx.h"
#include "../CConfigManager.h"

#include "../Bridge/CUserBridge.h"

class CRouteServerTCP:public CNetworkPublicSelect
{
public:

private:
	/*
		严格来说是SO_SNDLOWAT长度.
		一般是协议长度倍数( 协议长度一般小于MTU  SO_SNDLOWAT>MTU>协议长度 )
	*/
	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];

	CPublicProtocolVerify ProtocolVerify;

public:
	CRouteServerTCP();
	~CRouteServerTCP();	

	int Accept();
	int Recv(int nSocketRecv);

	void Close(int nNetKey);
	void CallBackClose(int nNetKey);

	int AddLogicElement(int nNetKey);
	void InitUserBridge(CUserBridge *pUserBridge, int nNetKey);

private:
	void TracerMe();
	void ReadFromConfigManager();
};



/*
 独立的线程控制
*/
class CRouteServerTCPThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);

private:

};

class CRouteServer
{
public:	
	CRouteServerTCP RouteServerTCP;
	CRouteServerTCPThread RouteServerTCPThread;

private:

public:	
	bool Init();
	void Start();

private:

};
