#include "CServerBinPlayTCP.h"
#include "../Logic/CWorldBinPlay.h"
#include "../CConfigManager.h"

extern volatile bool g_bQuit;
extern CWorldBinPlay g_WorldBinPlay;

//
//CServerBinPlayTCP
//
//
//public
//
CServerBinPlayTCP::CServerBinPlayTCP()
{
	ReadFromConfigManager();
	TracerMe();

	InitSocketTCPS();
	ServerIOCP.Create();

	ProtocolVerify.SetVersion1(name_bpmsg_protocol::BP_ORADER_ACTION_MAX);
	
	Init();
}

CServerBinPlayTCP::~CServerBinPlayTCP()
{

}

bool CServerBinPlayTCP::Init()
{
	LockUserList.UserList.ManualAlloct( CConfigManager::GetMaxConnectItem() );	
	Element_t *p = LockUserList.GetListFreeHead();

	for(int i=0; i<CConfigManager::GetMaxConnectItem(); ++i)
	{
		p->element.InServerIOCP.nResIdenti = i;
		p = p->pNext;
	}

	return true;
}


void CServerBinPlayTCP::TracerMe()
{
	printf("\nCServerBinPlayTCP:TracerMe\n");
	printf("Listen:ports=%d		ip=%s \n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));
}

void CServerBinPlayTCP::CallBackTracerMe()
{
	g_WorldBinPlay.CallBackTracerMe();
	printf("\nCServerBinPlayTCP:TracerMe\n");
	printf("LockUserList Sum Use:%d\n", LockUserList.GetSumElementUse());
	printf("LockUserList Sum Free:%d\n", LockUserList.GetSumElementFree());
}

//
//private
//
void CServerBinPlayTCP::ReadFromConfigManager()
{
	CConfigManager::ReadPlayIOCPLocal(&nPort, &nIP);	
}

CMRole * CServerBinPlayTCP::AddLogicElement(int nIndenti)
{
	CMRole *pMRole;
	pMRole = g_WorldBinPlay.MRoleManager.MRoleAdd( nIndenti );

	if( NULL==pMRole )
	{
		printf("Failed, CServerBinPlayTCP::AddLogicElement\n");
		return NULL;
	}

	MsgTest1SetNavi(pMRole);

	return pMRole;
}

void CServerBinPlayTCP::MsgTest1SetNavi(CMRole *pMRole)
{
	//一线，一号BIN服务器
	pMRole->MRoleHead.UserRouteNavi.SetIdentiLine(0);
	pMRole->MRoleHead.UserRouteNavi.SetIdentiBin(0);
	pMRole->MRoleHead.UserRouteNavi.SetResIdentiInBin(0);
}



void CServerBinPlayTCP::Accept()
{
	/*
		从网络池中取出对象进行accept,如果失败则回收；如果成功则申请逻辑对象。
		如果对象池为空，则进行延迟等待，暂时不accept
	*/
	IOCP_PLAY_KEY *pIOCPKey = LockUserList.GetMallocElement();

	if( NULL==pIOCPKey )
	{
		printf("Warning, CServerBinPlayTCP::Accept():Connect Full\n");		
		Sleep(1000);
		return;
	}

	IOCP_PLAY_KEY *pNetElement = pIOCPKey;

	pNetElement->nTypeIOCP = name_play_iocp::TYPE_IOCP_ACCEPT;
	int *pSocketAccept = &pNetElement->nSocket;
	int nSizeAddr = sizeof(pNetElement->SenderAddr);
	sockaddr *pSockAddr = (sockaddr *)&pNetElement->SenderAddr;

	*pSocketAccept = WSAAccept(this->nSocket, pSockAddr, &nSizeAddr, NULL, 0);

	if( SOCKET_ERROR==*pSocketAccept )
	{
		Close(pIOCPKey);		
		return;
	}

	AddLogicElement(pNetElement->InServerIOCP.nResIdenti);

	ServerIOCP.AssociateSocket(*pSocketAccept, (ULONG_PTR)pIOCPKey);

	printf("warning, IOCP accept and AssociateSocket a socket:%d\n", *pSocketAccept);	

	if( -1==Recv(pIOCPKey, name_msg_protocol::MSG_HEAD_BASE_SIZE, name_play_iocp::TYPE_IOCP_RECV_HEAD) )
	{
		printf("Err, CServerBinPlayTCP::Accept:Recv:%d\n", WSAGetLastError());
	}
}

int CServerBinPlayTCP::Recv(IOCP_PLAY_KEY *pIOCPKey, int nRecvSize, int nTypeIOCP)
{
	int nResult;
	IOCP_PLAY_KEY *pUserBridgeNet = pIOCPKey;

	pUserBridgeNet->InitRecv(nRecvSize, nTypeIOCP);

	nResult = WSARecv(pUserBridgeNet->nSocket, &pUserBridgeNet->WSADataBuf, 1, &pUserBridgeNet->nRecvBytes,
		             &pUserBridgeNet->nWSARecvFlag, &pUserBridgeNet->OverlappedRecv, NULL);

	if( SOCKET_ERROR==nResult )
	{
		if( WSAGetLastError() != WSA_IO_PENDING )
		{			
			Close(pIOCPKey);
			g_WorldBinPlay.CallBackClose( pUserBridgeNet->InServerIOCP.nResIdenti );
			return -1;
		}
	}

	return 0;
}

void CServerBinPlayTCP::Close(IOCP_PLAY_KEY *pIOCPKey)
{	
	/*
		先释放套接字本身，然后再从池里释放
	*/
	closesocket( pIOCPKey->nSocket);
	
	Element_t* p = LockUserList.GetElementAtID( pIOCPKey->InServerIOCP.nResIdenti);
	if( NULL==p )
	{
		printf("Warning, CServerBinPlayTCP::Close,NULL==p. id=%d\n", pIOCPKey->InServerIOCP.nResIdenti);
		return;
	}
	LockUserList.Erase( p );
}


//
//CServerBinPlayThread
//
unsigned int CServerBinPlayThread::ThreadStartAddr(void *pArguments)
{
	//debug;
	static int i=0;
	++i;
	printf("CServerBinPlayTCP::ThreadStartAddr:%d \n", i);	

	CServerBinPlayTCP *pServerBinPlay = (CServerBinPlayTCP*)pArguments;

	DWORD dwNumBytes;
	IOCP_PLAY_KEY* pIOCPKey;
	OVERLAPPED *pOverLapped;

	while( true!=g_bQuit )
	{
		int nResult;
		BOOL bResult;
		bResult = pServerBinPlay->ServerIOCP.GetStatus( (ULONG_PTR*)&pIOCPKey, &dwNumBytes, &pOverLapped, INFINITE);
		if( false==bResult && NULL==pOverLapped) //    
		{
			printf("Err,ServerIOCP.GetStatus:%d\n", WSAGetLastError());			
			break;
		}
		else if( 0==dwNumBytes/*end of file*/ || (false==bResult && NULL!=pOverLapped) )
		{
			printf("Warning, ServerIOCP.GetStatus:Close:%d\n", WSAGetLastError());
			goto element_close;				
		}

		bool bMsgSize;
		MsgBaseHead* pMsgBaseHead = (MsgBaseHead*)pIOCPKey->BufferRecv;

		switch (pIOCPKey->nTypeIOCP)
		{
		case name_play_iocp::TYPE_IOCP_RECV_HEAD:
			bMsgSize = pServerBinPlay->ProtocolVerify.IsMsgSize(pMsgBaseHead->nSizeOfMsg, pIOCPKey->WSADataBuf.len, dwNumBytes);

			if( false==bMsgSize )
			{					
				printf("Waring, TYPE_IOCP_RECV_HEAD:false==IsMsgSize\n");
				goto element_close;				
			}

			//
			//本地执行命令,需要验证
			if( 0==pMsgBaseHead->nRoutePriority )
			{
				if( false==pServerBinPlay->ProtocolVerify.IsMsgAction(pMsgBaseHead->__nActionOrder) )
				{
					printf("Warning, TYPE_IOCP_RECV_HEAD:false==IsMsgAction\n");					
					goto element_close;	
				}
			}

			nResult = pServerBinPlay->Recv(pIOCPKey, pMsgBaseHead->nSizeOfMsg-name_msg_protocol::MSG_HEAD_BASE_SIZE, 
										   name_play_iocp::TYPE_IOCP_RECV_CONTENT);	
			if( -1==nResult )
			{
				printf("Warning, TYPE_IOCP_RECV_HEAD:Recv:%d\n", WSAGetLastError());
			}

			break;

		case name_play_iocp::TYPE_IOCP_RECV_CONTENT:
			if( !pServerBinPlay->ProtocolVerify.IsMsgSize(pMsgBaseHead->nSizeOfMsg, pIOCPKey->WSADataBuf.len, dwNumBytes) )
			{				
				printf("Warning, TYPE_IOCP_RECV_CONTENT:false==IsMsgSize\n");
				goto element_close;					
			}
			else
			{
				CUserBridge    UserBridge;

				pServerBinPlay->InitUserBridge(&UserBridge, pIOCPKey);
				
				if( -1==g_WorldBinPlay.ResolveMsg(pMsgBaseHead, &UserBridge) )
				{
					goto element_close;	
				}

				nResult = pServerBinPlay->Recv(pIOCPKey, name_msg_protocol::MSG_HEAD_BASE_SIZE, name_play_iocp::TYPE_IOCP_RECV_HEAD);
				if( -1==nResult )
				{
					printf("Err, TYPE_IOCP_RECV_CONTENT:Recv:%d\n", WSAGetLastError());
				}
				
			}
			break;

element_close:      
		case -2010: /*专门用来关闭*/
			{
				pServerBinPlay->Close(pIOCPKey);
				g_WorldBinPlay.CallBackClose( pIOCPKey->InServerIOCP.nResIdenti );
			}
			break;

		default:
			printf("Waring, ServerIOCP.GetStatus:switch default\n");			
		}

		Sleep(1000);
	}

	printf("Warning, CServerBinPlayTCP::ThreadStartAddr:%d\n", i);	

	return 0;
}


//
//Other

void CServerBinPlayTCP::InitUserBridge(CUserBridge* pUserBridge, IOCP_PLAY_KEY *pNetElement)
{
	pUserBridge->UserBridgeNet.nInNetPoolRes = pNetElement->InServerIOCP.nResIdenti;
	pUserBridge->UserBridgeNet.nSocket = pNetElement->nSocket;
	pUserBridge->UserBridgeNet.SenderAddr = pNetElement->SenderAddr;

}

void CServerBinPlayThread::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );
}

//
//CServerBinPlayThreadAccept
//
unsigned int CServerBinPlayThreadAccept::ThreadStartAddr(void *pArguments)
{
	printf("CServerBinPlayTCP::ThreadStartAddrAccept:start!\n");	

	CServerBinPlayTCP *pServerBinPlay = (CServerBinPlayTCP*)pArguments;

	while( g_bQuit!=true )
	{
		pServerBinPlay->Accept();
		pServerBinPlay->CallBackTracerMe();
	}

	printf("CServerBinPlayTCP::ThreadStartAddrAccept:end!\n");	

	return 0;
}

void CServerBinPlayThreadAccept::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );	
}
//
//CServerBinPlay
//
CServerBinPlay::~CServerBinPlay()
{
	delete []pServerBinPlayThread;
}

bool CServerBinPlay::Init( int nThreadOfNumber)
{
	pServerBinPlayThread = new CServerBinPlayThread[nThreadOfNumber];

	return true;
}

void CServerBinPlay::Start(int nThreadOfIndex)
{
	pServerBinPlayThread[nThreadOfIndex].Start(&ServerBinPlayTCP);
}

void CServerBinPlay::StartAccept()
{
	ServerBinPlayThreadAccept.Start(&ServerBinPlayTCP);
}