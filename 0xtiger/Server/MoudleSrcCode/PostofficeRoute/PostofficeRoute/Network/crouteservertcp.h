/*
�ܼ򵥵�����㣬ʵ��TCP(Select)��һЩЭ����ȷ�ļ�⡣
Э��ľ�����CWorldPlay����
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
		�ϸ���˵��SO_SNDLOWAT����.
		һ����Э�鳤�ȱ���( Э�鳤��һ��С��MTU  SO_SNDLOWAT>MTU>Э�鳤�� )
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
 �������߳̿���
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
