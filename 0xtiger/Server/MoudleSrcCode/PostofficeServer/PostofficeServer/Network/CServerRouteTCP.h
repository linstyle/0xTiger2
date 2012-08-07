#pragma

#include "../stdafx.h"
#include "0x_Network.h"
#include "CServerRouteData.h"
#include "../Bridge/CUserBridge.h"

/*
  �����ʾ�·�ɵĿͻ��˴���
  ���̣߳���ռʽ����
*/



class CServerRouteTCP:public CCommonSocket/*�������׽���*/
{
public:
	bool bIsConnect;

	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];
	char BufferSend[name_msg_protocol::SOCKET_BUFF_SIZE_EX];

	CPublicProtocolVerify ProtocolVerify;

private:

public:
	CServerRouteTCP();
	~CServerRouteTCP();	

	void Connect();
	int  Recv();
	void Close();
	void CallBackClose();

	void InitUserBridge(CUserBridge *pUserBridge, int nNetKey);

	void SayHelloWorld();
	void UpdatePeopleToRoute();	

private:
	void TracerMe();
	void ReadFromConfigManager();	

	int Send(MsgBaseHead *pMsgBaseHead );
	
};

/*
 �������߳̿���
*/
class CServerRouteThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);
	
private:
};

class CServerRoute
{
public:
	CServerRouteTCP ServerRouteTCP;
	CServerRouteThread ServerRouteThread;

private:

public:
	bool Init();
	void Start();

private:

};

