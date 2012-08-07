#pragma once

#include "../stdafx.h"
#include "0x_Network.h"
#include "CLocalNetworkPublic.h"
#include "../Bridge/CUserBridge.h"

typedef CUserBridge IOCP_PLAY_KEY;

namespace name_playclient_udp
{
	const int TRY_GETLOGIN_MAX = 3;
};

class CPlayRouteUDP:public CCommonSocket
{
public:
	

private:
	LOGIN_INFO LoginInfo;
	volatile bool bGetLoginInfo;

	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];	
	CPublicProtocolVerify PublicProtocolVerify;

public:
	CPlayRouteUDP();
	~CPlayRouteUDP();

	int  StartAskLoginInfo();

	bool GetbGetLoginInfo();
	void SetbGetLoginInfo(bool b);

	LOGIN_INFO *GetLoginInfo();

private:
	void TracerMe();
	void ReadFromConfigManager();

	int  Connect();
	int  Send(MsgBaseHead* pMsgBaseHead);
	int  Recv();
};


/*
 独立的线程控制
*/
class CPlayRouteUDPThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);
	
private:
};

class CPlayRoute
{
public:	
	CPlayRouteUDP PlayRouteUDP;
	CPlayRouteUDPThread PlayRouteUDPThread;

private:

public:
	bool Init();
	void Start();

private:

};