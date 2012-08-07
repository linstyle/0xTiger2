#pragma once

#include "../stdafx.h"
#include "0x_Network.h"
#include "../Bridge/CUserBridge.h"

/*
	有连接进来时，连接池不断的释放出对象，然后不断的回收，如果关闭的话
*/

typedef CServerIOCPData IOCP_PLAY_KEY;

class CServerBinPlayTCP:public CCommonSocket
{
public:
	CLockListOfArray<IOCP_PLAY_KEY, 0, true> LockUserList;
	typedef CListOfArray<IOCP_PLAY_KEY, 0, true>::ELEMENT Element_t;

	CServerIOCP  ServerIOCP;
	CPublicProtocolVerify ProtocolVerify;

private:

public:
	CServerBinPlayTCP();
	~CServerBinPlayTCP();

	bool Init();

	void  Accept();
	int Recv(IOCP_PLAY_KEY *pIOCPKey, int nRecvSize, int nTypeIOCP);
	void Close(IOCP_PLAY_KEY *pIOCPKey);

	void CallBackTracerMe();
	CMRole* AddLogicElement(int nIndenti);
	/*
		debug模拟
	*/
	void MsgTest1SetNavi(CMRole *pMRole);

private:
	void TracerMe();
	
	void ReadFromConfigManager();

//
//other
public:
	void InitUserBridge(CUserBridge* pUserBridge, IOCP_PLAY_KEY *pNetElement);
};

/*
 独立的线程控制
*/
class CServerBinPlayThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);
	void virtual Start(void *pArguments);
	
private:
};

class CServerBinPlayThreadAccept:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);
	void virtual Start(void *pArguments);

private:

	
};

class CServerBinPlay
{
public:
	CServerBinPlayTCP ServerBinPlayTCP;
	CServerBinPlayThread *pServerBinPlayThread;
	CServerBinPlayThreadAccept ServerBinPlayThreadAccept;

private:

public:
	~CServerBinPlay();
	bool Init( int nThreadOfNumber );
	void Start( int nThreadOfIndex);
	void StartAccept();

private:

};