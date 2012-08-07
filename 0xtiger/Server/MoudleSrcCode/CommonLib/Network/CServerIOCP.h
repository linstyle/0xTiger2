#pragma once

#include <Winsock2.h>
#include "0x_Exception.h"
#include "Network/CNetworkPublic.h"

/*
部分代码参考《windows 核心编程 5th》
*/

namespace name_play_iocp
{
	//
	//感兴趣的事件类型
	const int TYPE_IOCP_CLOSE = 0;
	const int TYPE_IOCP_ACCEPT = 1;
	const int TYPE_IOCP_RECV_HEAD = 2;
	const int TYPE_IOCP_RECV_CONTENT = 3;
	const int TYPE_IOCP_SEND = 4;
};

/*
	在CServerIOCPData上的记录信息
*/
struct IN_SERVERIOCP
{
	int nResIdenti;
};

class CServerIOCPData
{
public:
	IN_SERVERIOCP InServerIOCP;
	//
	//客户端套接字信息
	int nSocket;			//4
	sockaddr_in SenderAddr; //16

	//
	//overlapped
	OVERLAPPED OverlappedRecv;//20
	OVERLAPPED OverlappedSend;
	WSABUF WSADataBuf;		  //8
	char BufferRecv[name_msg_protocol::SOCKET_BUFF_SIZE_EX];
	char BufferSend[name_msg_protocol::SOCKET_BUFF_SIZE_EX];
	
	DWORD nSendBytes;
	DWORD nRecvBytes;
	DWORD nWSARecvFlag;
	DWORD nWSASendFlag;

	int nTypeIOCP;
	
private:

public:
	CServerIOCPData()
	{
        OverlappedSend.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Set the event for writing so that packets
        // will not be sent to the completion port when
        // a write finishes.
        OverlappedSend.hEvent = (HANDLE)( (DWORD)OverlappedSend.hEvent | 0x1);
	}

	~CServerIOCPData()
	{
		CloseHandle( (HANDLE) ( (DWORD_PTR)OverlappedSend.hEvent & ~1) );
	}

	void InitRecv(int nRecvSize, int _nTypeIOCP)
	{
		memset( &OverlappedRecv, 0, sizeof(OverlappedRecv) );
		WSADataBuf.buf = BufferRecv;
		WSADataBuf.len = nRecvSize;
		nWSARecvFlag = 0;
		nTypeIOCP = _nTypeIOCP;

		if( name_play_iocp::TYPE_IOCP_RECV_CONTENT==_nTypeIOCP )
		{
			WSADataBuf.buf = BufferRecv+name_msg_protocol::MSG_HEAD_BASE_SIZE;
		}
	}
	void InitSend()
	{
		memset( &OverlappedSend, 0, sizeof(OverlappedSend) );
		WSADataBuf.buf = BufferSend;		
		nWSASendFlag = 0;
	}

private:
};

class CServerIOCP 
{
public:
	CServerIOCP() 
	{
		m_hIOCP = NULL; 
	}

	~CServerIOCP() 
	{ 
		if (m_hIOCP != NULL) 
			chVERIFY(CloseHandle(m_hIOCP)); 
	}


	BOOL Close() 
	{
		BOOL bResult = CloseHandle(m_hIOCP);
		m_hIOCP = NULL;
		return(bResult);
	}

	BOOL Create(int nMaxConcurrency = 0) 
	{
		m_hIOCP = CreateIoCompletionPort(
			INVALID_HANDLE_VALUE, NULL, 0, nMaxConcurrency);
		chASSERT(m_hIOCP != NULL);
		return(m_hIOCP != NULL);
	}

	BOOL AssociateDevice(HANDLE hDevice, ULONG_PTR CompKey) 
	{
		BOOL fOk = (CreateIoCompletionPort(hDevice, m_hIOCP, CompKey, 0) 
			== m_hIOCP);
		chASSERT(fOk);
		return(fOk);
	}

	BOOL AssociateSocket(SOCKET hSocket, ULONG_PTR CompKey) 
	{
		return(AssociateDevice((HANDLE) hSocket, CompKey));
	}

	BOOL PostStatus(ULONG_PTR CompKey, DWORD dwNumBytes = 0, 
		OVERLAPPED* po = NULL) 
	{

			BOOL fOk = PostQueuedCompletionStatus(m_hIOCP, dwNumBytes, CompKey, po);
			chASSERT(fOk);
			return(fOk);
	}

	BOOL GetStatus(ULONG_PTR* pCompKey, PDWORD pdwNumBytes,
		OVERLAPPED** ppo, DWORD dwMilliseconds = INFINITE) 
	{

			return(GetQueuedCompletionStatus(m_hIOCP, pdwNumBytes, 
				pCompKey, ppo, dwMilliseconds));
	}

private:
	HANDLE m_hIOCP;
};