#pragma once

#include "../stdafx.h"
#include "Network/CNetworkPublic.h"
#include "../Bridge/CUserBridge.h"

/*
	与PostofficeServer通信(数据包转发)，并且解析其中的play数据
*/

class CBinServerPlayTCP:public CCommonSocket
{
public:
	bool bIsConnect;
	bool bIsLoginServer;

	/*
		连接到第几个网关，序号从0开始依次递增
	*/
	int nConnectPostofficeIndex;

	CPublicProtocolVerify ProtocolVerify;

private:
	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];
	char BufferSend[name_msg_protocol::SOCKET_BUFF_SIZE_EX];

public:
	CBinServerPlayTCP();
	~CBinServerPlayTCP();

	void Init();

	void Connect();
	int Recv();
	
	void Close();

	void InitUserBridge(CUserBridge *pUserBridge, int nNetKey);

	void SayHelloWorld();
	int LoginServer();

private:
	void TracerMe();
	void ReadFromConfigManager();

	int Send(MsgBaseHead* pMsgBaseHead);	
	
};

/*
	独立的线程控制
*/
class CBinServerPlayThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);
	
private:
};

class CBinServerPlay
{
public:	
	CBinServerPlayTCP *pBinServerPlayTCP;
	CBinServerPlayThread BinServerPlayThread;

private:

public:
	CBinServerPlay();
	~CBinServerPlay();
	bool Init();
	void Start();
	void Release();

private:

};



