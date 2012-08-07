/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/14                                                         
    ����˵����  �����������
*/
#pragma once
#pragma comment(lib, "Mswsock.lib")

#include <assert.h>
#include "GlobalType.h"
#include "CNetObject.h"
#include "CIOCP.h"
#include <mswsock.h>

namespace name_netobject
{
	const int nAcceptIdenti=0;
	const int nConnectIdenti=1;
};

/*
	Connect(),Accept()
	�����������Ѿ��ѵײ������ʵ�֣��û���ʹ�õ�ʱ����Ը����Լ���Ҫ����������������
	�������һЩ����ļ�¼�ȵȣ�Ȼ�󷵻ػ����Connect/Accept()��

	����ֵ: -1ʧ��
	0 �ɹ�
	1 �Ѿ�����״̬��
*/
class ILocalObjectConnect:public CSocketAPI
{
public:
	void Init(const char *name, ULONG nIP, USHORT nPort);
	virtual ~ILocalObjectConnect();

	virtual int Connect();
	bool IsConnect();
	void ResetConnect();
	void SetAutoConnect(bool b);

	CIOCPData * GetIOCPData();
	SOCKET GetSocket();
	ULONG GetIP();
	USHORT GetPort();
	const char* GetName();

private:
	bool InitConnect();

public:


private:
	char m_szName[40];
	SOCKET m_nSocket;
	USHORT m_nPort;
	ULONG  m_nIP;	

	volatile bool m_bConnect;
	bool m_bAutoConnect;
	sockaddr_in m_ConnectAddr;
	CIOCPData m_IOCPData;
};


class ILocalObjectAccept:public CSocketAPI
{
public:
	virtual ~ILocalObjectAccept();

	void Init(const char *name, ULONG nIP, USHORT nPort);
	int Accept(CIOCPData *p);

	SOCKET GetSocket();
	ULONG GetIP();
	USHORT GetPort();
	const char* GetName();

private:
	bool InitAccept(CIOCPData *p);
	void InitAccpetExlpfn();
	
public:
	WSAOVERLAPPED  m_OverlappedAccept;

	LPFN_ACCEPTEX m_lpfnAcceptEx;

private:	
	char m_szName[40];
	SOCKET m_nSocket;
	USHORT m_nPort;
	ULONG  m_nIP;

	int  m_nAcceptExCount;
};
