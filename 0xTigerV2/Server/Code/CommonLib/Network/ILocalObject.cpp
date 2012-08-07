#include "StdAfx.h"
#include "ILocalObject.h"

void ILocalObjectConnect::Init(const char *name, ULONG nIP, USHORT nPort)
{
	memset(m_szName, 0, 40);
	strncpy(m_szName, name, 36);

	m_bConnect = false;
	m_bAutoConnect = true;

	m_nIP = nIP;
	m_nPort = nPort;
}

ILocalObjectConnect::~ILocalObjectConnect()
{
	closesocket(m_nSocket);	
}


int ILocalObjectConnect::Connect()
{
	if( true==m_bConnect )
	{
		return 1;
	}

	if( false==InitConnect() )
	{
		return -1;
	}
	/*
		windows�Է��������������һ���߳���(debug��)
	*/
	int nResult;
	nResult = ConnectNonb(m_nSocket, (sockaddr*)&m_ConnectAddr, sizeof(m_ConnectAddr), 2);
	if( -1==nResult )
	{				
		printf("err,");
		ResetConnect();
		return -1;
	}
	
	m_bConnect = true;

	return 0;
}

bool ILocalObjectConnect::InitConnect()
{
	m_IOCPData.nEvent = IOCP_EVENT_ACCEPT_CONNECT;	
	if( false==InitSocketTCPC(m_nSocket, m_nIP, m_nPort))
	{
		return false;
	}
	ZeroMemory(&m_ConnectAddr, sizeof(m_ConnectAddr));
	m_ConnectAddr.sin_family	= AF_INET;
	m_ConnectAddr.sin_port	    = htons(m_nPort);
	m_ConnectAddr.sin_addr.s_addr = m_nIP;

	return true;
}

void ILocalObjectConnect::ResetConnect()
{
	if(false==m_bAutoConnect)
	{
		closesocket(m_nSocket);	
		m_bConnect = true;			
	}
	else
	{
		closesocket(m_nSocket);
		m_bConnect = false;		
	}
	m_IOCPData.Init();
}

void ILocalObjectConnect::SetAutoConnect(bool b)
{
	m_bAutoConnect = b;
}

bool ILocalObjectConnect::IsConnect()
{
	return true==m_bConnect;
}

CIOCPData *ILocalObjectConnect::GetIOCPData()
{
	return &m_IOCPData;
}

SOCKET ILocalObjectConnect::GetSocket()
{
	return m_nSocket;
}

ULONG ILocalObjectConnect::GetIP()
{
	return m_nIP;
}

USHORT ILocalObjectConnect::GetPort()
{
	return m_nPort;
}

const char* ILocalObjectConnect::GetName()
{
	return m_szName;
}


void ILocalObjectAccept::Init(const char *name, ULONG nIP, USHORT nPort)
{
	memset(m_szName, 0, 40);
	strncpy(m_szName, name, 36);
	
	m_nSocket = 0;
	m_nPort = nPort;
	m_nIP = nIP;

	m_nAcceptExCount = 10;
	m_lpfnAcceptEx = NULL;

	/*
		��ȷ��ÿ��Ҫ��OverlappedRecv�Ƿ�Ҫ���㣬�����Ҫ��Ӱ��Event�Ĵ�����
		���������ͬ����Event�����򷵻�ԭ���ģ������ظ�����
		������û��ResetEvent����Ҳ����������
	*/
	memset(&m_OverlappedAccept, 0, sizeof(m_OverlappedAccept));
	m_OverlappedAccept.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	INITASSERT( NULL==m_OverlappedAccept.hEvent );

	InitSocketTCPS(m_nSocket, m_nIP, m_nPort);
	InitAccpetExlpfn();
}

ILocalObjectAccept::~ILocalObjectAccept()
{
	closesocket(m_nSocket);	
	CloseHandle(m_OverlappedAccept.hEvent);
}

int ILocalObjectAccept::Accept(CIOCPData *p)
{
	assert(NULL!=p);

	if( false==InitAccept(p) )
	{
		return -1;
	}

	//printf("Notic,Accept Prepare,:%d\n", p->nSocket);

	int nResult;
	nResult= m_lpfnAcceptEx(m_nSocket,
							p->nSocket,
							p->BufferPacket, 
							0,
							sizeof(sockaddr_in) + 16, 
							sizeof(sockaddr_in) + 16, 
							&p->nRecvBytes, 
							&m_OverlappedAccept);

	if(0==nResult)
	{
		if(WSAGetLastError() != WSA_IO_PENDING)
		{
			/* �����ժ¼apache
			We can get here when:
			* 1) the client disconnects early
			* 2) TransmitFile does not properly recycle the accept socket (typically
			*    because the client disconnected)
			* 3) there is VPN or Firewall software installed with buggy AcceptEx implementation
			* 4) the webserver is using a dynamic address that has changed
			   �ҵĲ���:
			   ������߳̽�������᷵�ؾ����Ч
			
			*/
			printf("Err");			
			return -1;
		}
	}

	/*
		�����Ϊ�г�ʱ�ģ����������ǳ���
	*/
	nResult = WaitForSingleObject(m_OverlappedAccept.hEvent, INFINITE);
	if( WAIT_FAILED==nResult )
	{
		printf("Err");			
		return -1;
	}


	return 0;
}

bool ILocalObjectAccept::InitAccept(CIOCPData *p)
{
	/*
		����Ҫע�� closesocket,����֮ǰ��ʱ���׽�
		����Ҳ�޷�����
	*/
	p->nEvent = IOCP_EVENT_ACCEPT_CONNECT;
	p->nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == p->nSocket) 
	{
		printf("Warning, INVALID_SOCKET == p->nSocket");
		return false;
	}

	ResetEvent(m_OverlappedAccept.hEvent);

	return true;
}

void ILocalObjectAccept::InitAccpetExlpfn()
{
	int nResult;
	DWORD   bytes;
	GUID GuidAcceptEx = WSAID_ACCEPTEX;

	nResult = WSAIoctl(m_nSocket, 
						SIO_GET_EXTENSION_FUNCTION_POINTER, 
						&GuidAcceptEx, 
						sizeof(GuidAcceptEx),
						&m_lpfnAcceptEx, 
						sizeof(m_lpfnAcceptEx), 
						&bytes, 
						NULL, 
						NULL);	

	INITASSERT( SOCKET_ERROR==nResult );
}

SOCKET ILocalObjectAccept::GetSocket()
{
	return m_nSocket;
}

ULONG ILocalObjectAccept::GetIP()
{
	return m_nIP;
}

USHORT ILocalObjectAccept::GetPort()
{
	return m_nPort;
}

const char* ILocalObjectAccept::GetName()
{
	return m_szName;
}