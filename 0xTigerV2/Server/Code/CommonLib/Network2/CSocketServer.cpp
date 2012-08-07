#include "stdafx.h"
#include "CSocketServer.h"

void CSocketServer::Init()
{
	memset(m_szName, 0, sizeof(m_szName));	
	m_nIP = 0;
	m_nPort = 0;
	m_nSocket = 0;

	//OS API��Ҫ
	memset(&m_OverlappedAccept, 0, sizeof(m_OverlappedAccept));
//	LPFN_ACCEPTEX m_lpfnAcceptEx;	�ⲿ��ʼ��
}

bool CSocketServer::Accept(CSocketClient *pSocketClient)
{
	IFn(NULL==pSocketClient)
	{
		return false;
	}

	if( false==InitAccept(pSocketClient) )
	{
		return false;
	}


	int nResult;
	nResult= m_lpfnAcceptEx(m_nSocket,
							pSocketClient->m_nSocket,
							NULL,  //��֪����NULL�᲻�����
							0,
							sizeof(sockaddr_in) + 16, 
							sizeof(sockaddr_in) + 16, 
							&pSocketClient->m_nRecvBytes, 
							&m_OverlappedAccept);

	if(0==nResult)
	{
		IFn(WSAGetLastError() != WSA_IO_PENDING)
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
			return false;
		}
	}

	/*
		�����Ϊ�г�ʱ�ģ����������ǳ���
	*/
	nResult = WaitForSingleObject(m_OverlappedAccept.hEvent, INFINITE);
	IFn( WAIT_FAILED==nResult )
	{
		return false;
	}


	return true;
}

bool CSocketServer::InitAccept(CSocketClient *pSocketClient)
{
	/*
		����Ҫע�� closesocket,����֮ǰ��ʱ���׽�
		����Ҳ�޷�����
	*/
	pSocketClient->m_nIOCPEvent = IOCP_EVENT_ACCEPT_CONNECT;
	pSocketClient->m_nSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	IFn(INVALID_SOCKET == pSocketClient->m_nSocket) 
	{
		return false;
	}

	IFn(FALSE== ResetEvent(m_OverlappedAccept.hEvent))
	{
		return false;
	}

	return true;
}

//
//CSocketServerManager::CSocketServerManager()
//{
//	m_nSocketServerCount=0;
//}
//
//CSocketServerManager::~CSocketServerManager()
//{
//	for (int i=0; i<m_nSocketServerCount; i++)
//	{
//		closesocket(m_SocketServer[i].m_nSocket);
//	}
//
//}
//
//bool CSocketServerManager::AddSocketServer(const char* pName, ULONG nListenIP, USHORT nListenPort)
//{
//	if (m_nSocketServerCount>=SOCKET_SERVER_COUNT)
//	{
//		LOGW("Warning, CSocketServerManager::AddSocketServer. m_nSocketServerCount(%d)>=SOCKET_SERVER_COUNT(%d)\n", m_nSocketServerCount, SOCKET_SERVER_COUNT);
//		return false;
//	}
//
//	SOCKET_SERVER *pSocketServer = m_SocketServer[m_nSocketServerCount];
//	
//	memset(pSocketServer->m_szName, 0 ,sizeof(pSocketServer->m_szName));
//	memcpy( pSocketServer->m_szName, pName, sizeof(pSocketServer->m_szName));
//	pSocketServer->m_nIP = nListenIP;
//	pSocketServer->m_nPort = nListenPort;
//
//	m_nSocketServerCount++;
//
//	return true;
//}
//
//bool CSocketServerManager::AddSocketServer(const char* pName, const char* pListenIP, USHORT nListenPort)
//{
//	if (m_nSocketServerCount>=SOCKET_SERVER_COUNT)
//	{
//		LOGW("Warning, CSocketServerManager::AddSocketServer. m_nSocketServerCount(%d)>=SOCKET_SERVER_COUNT(%d)\n", m_nSocketServerCount, SOCKET_SERVER_COUNT);
//		return false;
//	}
//
//	return AddSocketServer(pName, inet_addr(pListenIP), nListenPort);
//}
//
//void CSocketServerManager::LoopAccept()
//{
//	
//}