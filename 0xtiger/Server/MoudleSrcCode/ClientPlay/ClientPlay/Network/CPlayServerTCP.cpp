#include "CPlayServerTCP.h"
#include "../CConfigManager.h"

extern volatile bool g_bQuit;

#include "../Logic/CWorldServerBin.h"
extern CWorldServerBin g_WorldServerBin;
//
//
//public
void CPlayServerTCP::TracerMe()
{
	printf("CPlayServerTCP:TracerMe---------------------\n");
	printf("Connect:ports=%d,	ip=%s\n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));	
}

CPlayServerTCP::CPlayServerTCP()
{	

}

bool CPlayServerTCP::Init()
{
	TracerMe();

	InitSocketTCPC();
	
	//iocp init
	ServerIOCP.Create();

	ProtocolVerify.SetVersion1(name_bpmsg_protocol::BP_ORADER_ACTION_MAX);
	return true;
}

CPlayServerTCP::~CPlayServerTCP()
{

}

//
//
//private
void CPlayServerTCP::ReadFromContent(LOGIN_INFO *pLoginInfo)
{
	nPort = pLoginInfo->nPort;
	nIP = pLoginInfo->nIP;

	Init();
	TracerMe();
}


int CPlayServerTCP::Connect()
{
	int nResult = ConnectNonb(nSocket, (sockaddr*)&Addr, sizeof(Addr), 3);

	if( -1== nResult )
	{
		printf("Err, Can't connect to server:%d\n", WSAGetLastError());
		return -1;
	}

	return SayHelloWorld();
}

int CPlayServerTCP::Send(MsgBaseHead* pMsgBaseHead)
{
	int nResult;

	nResult = SendnTCP(nSocket, (char*)pMsgBaseHead, pMsgBaseHead->nSizeOfMsg);
	if( -1==nResult )
	{
		Close();
	}

	return nResult;
}

int CPlayServerTCP::Recv(IOCP_PLAY_KEY *pPlayKey, int nRecvSize, int nTypeIOCP)
{
	int nResult;
	CUserBridgeNet *pUserBridgeNet = &pPlayKey->UserBridgeNet;

	pUserBridgeNet->InitRecv(nRecvSize, nTypeIOCP);

	nResult = WSARecv(pUserBridgeNet->nSocket, &pUserBridgeNet->WSADataBuf, 1, &pUserBridgeNet->nRecvBytes,
					 &pUserBridgeNet->nWSARecvFlag, &pUserBridgeNet->OverlappedRecv, NULL);

	if( SOCKET_ERROR==nResult )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{
			Close();
			return -1;
		}
	}

	return 0;
}

int CPlayServerTCP::SayHelloWorld()
{
	MsgSayHello HelloWorld;	

	strcpy(HelloWorld.Buffer, "ClientPlay Say: Hello!");

	if( Send(&HelloWorld)<=0 )
	{
		printf("Err, CPlayServerTCP::HelloWorld:%d\n", WSAGetLastError());		
		return -1;
	}

	return 0;
}

int CPlayServerTCP::Test2()
{
	MsgTest2 MsgT2;

	if( Send(&MsgT2)<=0 )
	{
		printf("Err, Send(&MsgTest2) :%d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}

int CPlayServerTCP::Test3()
{
	int nResult;
	MsgTest3 MsgT3;

	MsgT3.nMoney = 1000;

	if( Send(&MsgT3)<=0 )
	{
		printf("Err, Send(&MsgTest3) :%d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}

void CPlayServerTCP::Close()
{
	
}


//
//CPlayServerTCP
//
unsigned int CPlayServerTCPThread::ThreadStartAddr(void *pArguments)
{
	printf("CPlayServerTCP::ThreadStartAddr:start! \n");	

	CPlayServerTCP *pPlayClientTCP = (CPlayServerTCP*)pArguments;
	CUserBridge *pUserBridge = new CUserBridge;

	bool bResult;
	IOCP_PLAY_KEY *pIOCPKey;
	DWORD dwNumBytes;
	OVERLAPPED *pOverLapped;

	//
	//connect一次即可
	if( -1==pPlayClientTCP->Connect() )
	{
		goto ThreadStartAddr_End;
	}
	pPlayClientTCP->ServerIOCP.AssociateSocket(pPlayClientTCP->nSocket, (ULONG_PTR)pUserBridge);

	//debug
	pPlayClientTCP->Test2();
	Sleep(3000);
	pPlayClientTCP->Test3();

	pUserBridge->UserBridgeNet.nSocket = pPlayClientTCP->nSocket;

	if( -1==pPlayClientTCP->Recv(pUserBridge, name_msg_protocol::MSG_HEAD_BASE_SIZE, name_play_iocp::TYPE_IOCP_RECV_HEAD) )
	{
		printf("Err, CServerBinPlayTCP::Accept:Recv:%d\n", WSAGetLastError());
	}	
	//end debug

	while( true!=g_bQuit)
	{
		bResult = pPlayClientTCP->ServerIOCP.GetStatus( (ULONG_PTR*)&pIOCPKey, &dwNumBytes, &pOverLapped, INFINITE);
		if( false==bResult && NULL==pOverLapped) //    
		{
			printf("ServerIOCP.GetStatus:%d \n", GetLastError());
			break;
		}
		else if( 0==dwNumBytes/*end of file*/ || (false==bResult && NULL!=pOverLapped) )
		{			
			printf("ServerIOCP.GetStatus:Close\n");
			break;
		}

		MsgBaseHead* pMsgBaseHead = (MsgBaseHead*)pIOCPKey->UserBridgeNet.BufferRecv;
		switch (pIOCPKey->UserBridgeNet.nTypeIOCP)
		{
		case name_play_iocp::TYPE_IOCP_RECV_HEAD:
			if( !pPlayClientTCP->ProtocolVerify.IsMsgSize(pMsgBaseHead->nSizeOfMsg, pIOCPKey->UserBridgeNet.WSADataBuf.len, dwNumBytes)
			 || !pPlayClientTCP->ProtocolVerify.IsMsgAction(pMsgBaseHead->__nActionOrder) )
			{
				printf("收到不合法数据包\n");
			}
			else
			{
				pPlayClientTCP->Recv(pIOCPKey, pMsgBaseHead->nSizeOfMsg-name_msg_protocol::MSG_HEAD_BASE_SIZE, 
											   name_play_iocp::TYPE_IOCP_RECV_CONTENT);	
			}
			
			break;

		case name_play_iocp::TYPE_IOCP_RECV_CONTENT:
			if( !pPlayClientTCP->ProtocolVerify.IsMsgSize(pMsgBaseHead->nSizeOfMsg, pIOCPKey->UserBridgeNet.WSADataBuf.len, dwNumBytes) )
			{
				printf("收到不合法数据包\n");
			}
			else
			{
				if( -1==g_WorldServerBin.ResolveMsg(pMsgBaseHead, pIOCPKey) )
				{
					printf("Warning, g_WorldServerBin.ResolveMsg Failed\n");
					goto ThreadStartAddr_End;
				}

				pPlayClientTCP->Recv(pIOCPKey, name_msg_protocol::MSG_HEAD_BASE_SIZE, name_play_iocp::TYPE_IOCP_RECV_HEAD);	
			}
			break;

		case name_play_iocp::TYPE_IOCP_SEND:
			//
			//主要针对场景服务器变更时需要
			break;

		default:
			printf("Warning, ServerIOCP.GetStatus:switch default\n");			
		}
		Sleep(1000);
	}

ThreadStartAddr_End:
	printf("CPlayServerTCP::ThreadStartAddr:end!\n");	
	//
	//clear
	delete pUserBridge;
	return 0;
}

void CPlayServerTCPThread::Start(void *pArguments)
{
	//
	//CREATE_SUSPENDED 注意，这里是睡眠状态
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, CREATE_SUSPENDED, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );	
}

int CPlayServerTCPThread::Resume()
{
	return ResumeThread(hThreadSelf);
}

//
//CPlayServer
//

bool CPlayServer::Init()
{
	return true;
}

void CPlayServer::Start()
{
	PlayServerTCPThread.Start(&PlayServerTCP);
}


