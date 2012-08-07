#include "stdafx.h"
#include "CSocketClient.h"
#include "CWindowsSlabManager.h"
#include "CSocketAPI.h"

CSocketClient*  MallocSocketClientObject()
{
	void *p = name_slab::kmem_malloc(sizeof(CSocketClient));	

	IFn( NULL==p )
	{
		return NULL;
	}

	CSocketClient *pSocketClient = new(p)CSocketClient;

	return pSocketClient;
}
void  FreeSocketClientObject(CSocketClient* p)
{
	//����C++����ԭ������������������
	//printf("CSocketRun::FreeNetObject, %x\n", p);
	IFn(NULL==p)
	{
		return;
	}
	p->~CSocketClient();

	name_slab::kmem_free((void*)p);
}

CSocketClient::CSocketClient()
{
	m_bAutoConnect = false;
	Init();
}

CSocketClient::~CSocketClient()
{
	closesocket(m_nSocket);
}

void CSocketClient::Init()
{
	m_nStepFlag = IOCP_STEP_INIT;
	m_nIP = m_nPort = m_nSocket = 0;

	m_RecvBuffer.Init(socket_circle_config::RECV_CIRCLE_LEN);
	m_SendBuffer.Init(socket_circle_config::SEND_CIRCLE_LEN);
	INIT_LIST_HEAD(&m_List);
}

int CSocketClient::Send(const char* pBuffer, int nBufferLen)
{
	if (NULL==pBuffer)
	{
		return -1;
	}

	return m_SendBuffer.WriteBufferAtom(pBuffer, nBufferLen);
}

int CSocketClient::FlushSend()
{
	int nResult;

	/*
		@���λ�����������������ĩβ��flush����
	*/
	nResult = FlushSendSub();
	if( -1==nResult )
	{
		return -1;
	}

	nResult = FlushSendSub();
	if( -1==nResult )
	{
		return -1;
	}

	return nResult;
}

int CSocketClient::FlushSendSub()
{
	int nResult;
	int nLen=0;
	const char *pSendBuffer;

	pSendBuffer = m_SendBuffer.GetReadBuffer(&nLen);

	nResult = CSocketAPI::SendnTCP(m_nSocket, pSendBuffer, nLen);
	if( -1==nResult )
	{
		return -1;
	}

	m_SendBuffer.ReadBufferFlush(nResult);
	if( nResult<nLen ) /*���ԣ����Ͳ���ȫ���ȴ��»�*/
	{				
		return 1;
	}

	return 0;
}

int CSocketClient::Recv()
{
	InitRecv();
	return RecvPacketStream();
}

void CSocketClient::InitRecv()
{
	InitRecv1();
	InitRecv2();	
	m_nWSARecvFlag = 0;
	m_nStepFlag = IOCP_STEP_RECV_ING;
	m_nIOCPEvent = IOCP_EVENT_RECV_BIG;
	memset(&m_OverlappedRecv, 0, sizeof(m_OverlappedRecv));
}
void CSocketClient::InitRecv1()
{
	int i;

	char *p = m_RecvBuffer.GetWriteBuffer1(&i);
	m_WSADataBuf[0].buf = p;
	m_WSADataBuf[0].len = i;
}

void CSocketClient::InitRecv2()
{
	int i;

	char *p = m_RecvBuffer.GetWriteBuffer2(&i);
	m_WSADataBuf[1].buf = p;
	m_WSADataBuf[1].len = i;
}

int CSocketClient::RecvPacketStream()
{
	int nResult;
	DWORD dwRecvBytes;

	nResult = WSARecv(m_nSocket, m_WSADataBuf, 2, &dwRecvBytes, &m_nWSARecvFlag, &m_OverlappedRecv, NULL);
	if( SOCKET_ERROR==nResult )
	{
		IFn( WSAGetLastError() != WSA_IO_PENDING )
		{
			/*
				�����쳣
				@һ�����׽��ֱ����쳣������ֱ������
				@һ����Ͷ�ݺ���յ����쳣������رյȵȡ�
			*/
			return -1;
		}
	}

	return 0;
}

int CSocketClient::Connect()
{
	if(false==InitConnect())
	{
		return -1;
	}

	/*
		windows�Է��������������һ���߳���(debug��)
	*/
	int nResult;
	nResult = CSocketAPI::ConnectNonb(m_nSocket, (sockaddr*)&m_ConnectAddr, sizeof(m_ConnectAddr), 0);
	IFn( -1==nResult )
	{
		return -1;
	}

	return 0;
}

bool CSocketClient::InitConnect()
{
	//m_nIOCPEvent = IOCP_EVENT_ACCEPT_CONNECT;	 ��������ûʲô����
	IFn( false==CSocketAPI::InitSocketTCPC(m_nSocket, m_nIP, m_nPort))
	{
		return false;
	}
	ZeroMemory(&m_ConnectAddr, sizeof(m_ConnectAddr));
	m_ConnectAddr.sin_family	= AF_INET;
	m_ConnectAddr.sin_port	    = htons(m_nPort);
	m_ConnectAddr.sin_addr.s_addr = m_nIP;

	return true;
}