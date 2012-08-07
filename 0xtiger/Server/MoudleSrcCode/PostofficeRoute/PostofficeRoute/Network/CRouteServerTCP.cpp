#include "CRouteServerTCP.h"
#include "../Logic/CWorldServer.h"

extern bool g_bQuit;
extern CWorldServer g_WorldServer;

//
//CRouteServerTCP
//
//
//public
CRouteServerTCP::CRouteServerTCP()
{	
	ReadFromConfigManager();
	TracerMe();
	
	InitSocketTCPS();
	FD_SET(nSocket, &SetRead);

	ProtocolVerify.SetVersion1(name_routemsg_protocol::ROUTE_ORADER_ACTION_MAX);
}

CRouteServerTCP::~CRouteServerTCP()
{

}

void CRouteServerTCP::TracerMe()
{
	printf("CRouteServerTCP:TracerMe---------------------\n");
	printf("Listen:ports=%d		ip=%s\n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));	
}

void CRouteServerTCP::Close(int nSocketClose)
{
	EraseFromReadSet(nSocketClose);		
}

/*
	Recv需要多次接收(头+体)，并且验证合法性。
	因此把资源操作放在外部，而消息提示放在内部 
*/
int CRouteServerTCP::Recv(int nSocketRecv)
{
	int nResult;		

	//
	//recv head with protocol. reasult: close or err 
	nResult = RecvnTCP(nSocketRecv, BufferRecv, name_msg_protocol::MSG_HEAD_BASE_SIZE);
	if( nResult<=0 )
	{		
		printf("Err, CRouteServerTCP::Recv Head Or Close Order:%d\n", WSAGetLastError());		
		return -1;
	}

	MsgBaseHead* pMsgHead = (MsgBaseHead*)BufferRecv;
	
	//
	//check head
	if( !ProtocolVerify.IsMsgSize(pMsgHead->nSizeOfMsg, 0, 0)
	 || !ProtocolVerify.IsMsgAction(pMsgHead->__nActionOrder) )
	{
		printf("收到不合法数据包!\n");		
		return -1;
	}

	//
	//recv content with protocol
	nResult = RecvnTCP(nSocketRecv, BufferRecv+name_msg_protocol::MSG_HEAD_BASE_SIZE, pMsgHead->nSizeOfMsg-name_msg_protocol::MSG_HEAD_BASE_SIZE);
	if( nResult<=0 )
	{
		printf("Err, CRouteServerTCP::Recv Content:%d\n", WSAGetLastError());		
		return -1;
	}

	CUserBridge UserBridge;

	InitUserBridge(&UserBridge, nSocketRecv);

	if( -1==g_WorldServer.ResolveMsg(pMsgHead, &UserBridge) )
	{
		printf("Err, CRouteServerTCP::g_WorldServer.ResolveMsg\n");
		return -1;
	}

	return 0;
}

int CRouteServerTCP::Accept()
{
	/*
		Accept关闭要注意：
		如果在accept失败，直接closesocket
		如果分配逻辑对象失败，直接EraseFromReadSet(网络对象方法)
	*/
	int nSocketAccept;
	u_long nNonBlock = 1;

	nSocketAccept = accept(nSocket, NULL, NULL);
	if( INVALID_SOCKET==nSocketAccept )
	{
		if( WSAGetLastError() != WSAEWOULDBLOCK )
		{
			return -1;
		}		
	}

	if( SOCKET_ERROR==ioctlsocket(nSocketAccept, FIONBIO, &nNonBlock) )
	{		
		printf("Err, CRouteServerTCP::Accept::ioctlsocket:%d\n", WSAGetLastError());
		closesocket(nSocketAccept);
		return 0;
	}
	//
	//添加到套接字数组里.GetConnectSum返回值包括listen套接字
	if( GetConnectSum()>CConfigManager::GetMaxConnectItem() || -1==AddToReadSet(nSocketAccept) )
	{		
		printf("CRouteServerTCP::Accept::CreateServerInfo full\n");
		closesocket(nSocketAccept);
		return 0;			
	}

	if( -1==AddLogicElement(nSocketAccept) )
	{
		printf("Failed, CRouteServerTCP::Accept:MallocLogicElement\n");
		EraseFromReadSet(nSocketAccept);
		return 0;
	}	
	
	printf("Warning, CRouteServerTCP::Accept:ok:%d\n", nSocketAccept);

	return 0;
}

void CRouteServerTCP::InitUserBridge(CUserBridge *pUserBridge, int nNetKey)
{
	pUserBridge->UserBridgeNet.nSocketSend = nNetKey;	
}

int CRouteServerTCP::AddLogicElement(int nNetKey)
{
	if( NULL== g_WorldServer.MRoleManager.MRoleAdd( nNetKey) )
	{
		return -1;
	}

	return 0;
}

void CRouteServerTCP::CallBackClose(int nNetKey)
{
	EraseFromReadSet(nNetKey);	
}

//
//private
//
void CRouteServerTCP::ReadFromConfigManager()
{
	CConfigManager::ReadRouteTCPListen(&nPort, &nIP);
}

//
//CRouteServerTCPThread
//
unsigned int CRouteServerTCPThread::ThreadStartAddr(void *pArguments)
{
	CRouteServerTCP *pRouteServerTCP = (CRouteServerTCP*)pArguments;

	printf("CRouteServerTCP start! \n");
	
	int nTotal=0;
	timeval TimeSelect;

	TimeSelect.tv_sec=1;
	TimeSelect.tv_usec=0;

	fd_set SetRead_g;
	while( g_bQuit!=true )
	{
		TimeSelect.tv_sec=1;
		TimeSelect.tv_usec=0;
		//
		//select无数据后，会自动删除无数据的套接字.需要重新set一次		
		SetRead_g = pRouteServerTCP->SetRead;

		nTotal = select(0, &SetRead_g, NULL, NULL, &TimeSelect);
		if( SOCKET_ERROR==nTotal )
		{
			printf("Err, CRouteServerTCP::select: %d\n", WSAGetLastError());			
			goto CRouteServerTCP_Quit;
		}

		if( FD_ISSET(pRouteServerTCP->nSocket, &SetRead_g) )
		{
			FD_CLR(pRouteServerTCP->nSocket, &SetRead_g);
			--nTotal;
			if( -1==pRouteServerTCP->Accept())
			{
				goto CRouteServerTCP_Quit;
			}
		}
		
		for(int i=0; nTotal>0 && i<CConfigManager::GetMaxConnectItem(); ++i)
		{
			if( -1==pRouteServerTCP->Recv(SetRead_g.fd_array[i]) )
			{
				pRouteServerTCP->Close(SetRead_g.fd_array[i]);
				g_WorldServer.CallBackClose(SetRead_g.fd_array[i]);
			}
			--nTotal;
		}

		//
		//这里可以做个智能的Sleep,如果上一回没收到数据，则进行Sleep;否则持续读取
		Sleep(1000);

		//debug
		g_RouteRand.TracerMe_All();
		g_WorldServer.CallBackTracerMe();
	}

CRouteServerTCP_Quit:

	printf("CRouteServerTCP quit! \n");

	return 0;
}

void CRouteServerTCPThread::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );		
}


//
//CRouteServer
//

bool CRouteServer::Init()
{

	return true;
}

void CRouteServer::Start()
{
	RouteServerTCPThread.Start(&RouteServerTCP);		
}