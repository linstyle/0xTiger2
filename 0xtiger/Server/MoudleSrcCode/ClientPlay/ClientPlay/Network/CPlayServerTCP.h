#pragma once

#include "../stdafx.h"
#include "0x_Network.h"
#include "CLocalNetworkPublic.h"
#include "../Bridge/CUserBridge.h"

typedef CUserBridge IOCP_PLAY_KEY;

class CPlayServerTCP:public CCommonSocket
{
public:
	CServerIOCP  ServerIOCP;
	CPublicProtocolVerify ProtocolVerify;

private:
	
public:
	CPlayServerTCP();
	~CPlayServerTCP();

	bool Init();
	void ReadFromContent(LOGIN_INFO *pLoginInfo);

	int Connect();
	void Close();
	int Recv(IOCP_PLAY_KEY *pPlayKey, int nRecvSize, int nTypeIOCP);

	int SayHelloWorld();
	//debug
	int Test3();
	int Test2();
	//end debug

private:
	void TracerMe();
	
	int Send(MsgBaseHead* pMsgBaseHead);
};



/*
 独立的线程控制
*/
class CPlayServerTCPThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);
	int Resume();
	
private:
};

class CPlayServer
{
public:	
	CPlayServerTCP PlayServerTCP;
	CPlayServerTCPThread PlayServerTCPThread;

private:

public:
	bool Init();
	void Start();

private:

};