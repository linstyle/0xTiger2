#pragma once

#include "../stdafx.h"
#include "Network/CNetworkPublic.h"
#include "../Bridge/CUserBridge.h"

/*
	��PostofficeServerͨ��(���ݰ�ת��)�����ҽ������е�play����
*/

class CBinServerPlayTCP:public CCommonSocket
{
public:
	bool bIsConnect;
	bool bIsLoginServer;

	/*
		���ӵ��ڼ������أ���Ŵ�0��ʼ���ε���
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
	�������߳̿���
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



