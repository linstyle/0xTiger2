/*
 �ܼ򵥵�����㣬ʵ��UDP��һЩЭ����ȷ�ļ�⡣
 Э��ľ�����CWorldPlay����

*/

#pragma once

#include "../stdafx.h"
#include "0x_Network.h"
#include "../CRoutePublic.h"
#include "../Bridge/CUserBridgeNet.h"


class CRoutePlayUDP:public CCommonSocket
{
public:

private:
	//
	//����Ķ����
	int nIdenti;	
	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];	

	CPublicProtocolVerify ProtocolVerify;
public:
	CRoutePlayUDP();
	~CRoutePlayUDP();

	//
	//nIndex:�ڼ�������
	bool Init(int nObjectOfIndex);
	int Recv();
	void Close(int nNetKey);

	int GetIdenti()
	{
		return nIdenti;
	}

private:
	void TracerMe();
	void ReadFromConfigManager(int nIndex);	

};


/*
 �������߳̿���
*/
class CRoutePlayUDPThread:public CThreadLife
{
public:

private:

public:
	static unsigned int __stdcall ThreadStartAddr(void *pArguments);

	void virtual Start(void *pArguments);
	int _ResumeThread();
	int _SetThreadIdealProcessor( int nProcessorOfIndex );

private:

};

class CRoutePlay
{
public:	
	CRoutePlayUDP *pRoutePlayUDP;
	CRoutePlayUDPThread *pRoutePlayUDPThread;

private:

public:
	~CRoutePlay();
	bool Init( int nThreadOfNumber );
	void Start( int nThreadOfIndex );


private:

};
