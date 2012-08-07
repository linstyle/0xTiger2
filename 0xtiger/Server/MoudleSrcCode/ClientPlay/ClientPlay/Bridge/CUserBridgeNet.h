#pragma once

#include "../stdafx.h"
#include "0x_Network.h"


//
//因为PlayClient和RouteClient的缘故(两者服务对象不一样)，该结构的若干信息有所冗余
class CUserBridgeNet
{
public:
	//
	//客户端套接字信息
	int nSocket;		//4
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
	CUserBridgeNet()
	{
        OverlappedSend.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        // Set the event for writing so that packets
        // will not be sent to the completion port when
        // a write finishes.
        OverlappedSend.hEvent = (HANDLE)( (DWORD)OverlappedSend.hEvent | 0x1);
	}

	~CUserBridgeNet()
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