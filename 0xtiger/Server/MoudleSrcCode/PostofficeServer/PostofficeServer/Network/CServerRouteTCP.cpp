#include "CServerRouteTCP.h"

#include "../CConfigManager.h"
#include "../Logic/CWorldRoute.h"

extern volatile bool g_bQuit;
extern CWorldRoute g_WorldRoute;

extern CServerRouteData ServerRouteData;
//
//CServerRouteTCP
//
//
//public
//
CServerRouteTCP::CServerRouteTCP()
{
	bIsConnect = false;

	ReadFromConfigManager();
	TracerMe();

	InitSocketTCPC(1);

	ProtocolVerify.SetVersion1(name_routemsg_protocol::ROUTE_ORADER_ACTION_MAX);
}

CServerRouteTCP::~CServerRouteTCP()
{
	
}

void CServerRouteTCP::TracerMe()
{
	printf("\nCServerRouteTCP:TracerMe\n");
	printf("Connect:ports=%d	ip=%s\n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));	
}

	             
void CServerRouteTCP::InitUserBridge(CUserBridge *pUserBridge, int nNetKey)
{
	pUserBridge->UserBridgeNet.nSocket = nNetKey;
}


void CServerRouteTCP::Connect()
{
	int nResult;
	sockaddr_in ConnectAddr;

	InitSocketTCPC();
	ZeroMemory(&ConnectAddr, sizeof(ConnectAddr));
	ConnectAddr.sin_family	    = AF_INET;
	ConnectAddr.sin_port	    = htons(nPort);
	ConnectAddr.sin_addr.s_addr = nIP;

	nResult = ConnectNonb(nSocket, (sockaddr*)&ConnectAddr, sizeof(ConnectAddr), 3);
	if( -1==nResult )
	{		
		printf("CServerRouteTCP::ThreadStartAddr:Connect:%d\n", WSAGetLastError());
		Close();
		return;
	}
	
	printf("CServerRouteTCP::ThreadStartAddr:Connect:ok\n");
	bIsConnect = true;

	SayHelloWorld();
}

void CServerRouteTCP::UpdatePeopleToRoute()
{
	CUserBridge UserBridge;
	
	MsgServerUpdatePeople MsgUpdatePeople;

	InitUserBridge( &UserBridge, nSocket);
	MsgUpdatePeople.nIP = ServerRouteData.GetPlayClientInfo()->nIP;
	MsgUpdatePeople.nPort = ServerRouteData.GetPlayClientInfo()->nPorts;
	MsgUpdatePeople.nBinIdenti = CConfigManager::GetGlobalIdenti();
	//MsgUpdatePeople.nPeople = 这个就交给play世界和route世界交互，网络层不参合

	if( -1==g_WorldRoute.UpdateRouteServerPeople(&MsgUpdatePeople, &UserBridge) )
	{
		Close();
		g_WorldRoute.CallBackClose( nSocket );	
	}
}

void CServerRouteTCP::SayHelloWorld()
{
	MsgSayHello HelloWorld;	

	strcpy(HelloWorld.Buffer, "PostofficeServer Say: Hello!");

	if( -1==Send(&HelloWorld) )
	{
		printf("Err, CServerRouteTCP::SayHelloWorld:%d\n", WSAGetLastError());		
	}
}


//
//private
//
void CServerRouteTCP::ReadFromConfigManager()
{
	CConfigManager::ReadConnectPostofficeRoute(&nPort, &nIP);
}


int CServerRouteTCP::Send(MsgBaseHead *pMsgBaseHead )
{
	int nResult;
	
	nResult = SendnTCP(nSocket, (const char*)pMsgBaseHead, pMsgBaseHead->nSizeOfMsg);
	if( nResult<=0 )
	{		
		Close();
		g_WorldRoute.CallBackClose( nSocket );
		return -1;
	}

	return 0;
}


int CServerRouteTCP::Recv()
{
	int nResult;		

	//debug, with select
	fd_set SetRead;
	int nTotal = 0;
	timeval TimeSelect;

	FD_ZERO(&SetRead);
	FD_SET(nSocket, &SetRead);
	TimeSelect.tv_sec=2;
	TimeSelect.tv_usec=0;

	nTotal = select(0, &SetRead, NULL, NULL, &TimeSelect);
	if( SOCKET_ERROR==nTotal )
	{
		printf("Err, CBinServerPlayTCP::Recv(): %d\n", WSAGetLastError());			
		goto recv_close;
	}
	if( nTotal<=0 )
	{
		return 0;
	}
	//end debug

	//
	//recv head with protocol. reasult: close or err 
	nResult = RecvnTCP(nSocket, BufferRecv, name_msg_protocol::MSG_HEAD_BASE_SIZE);
	if( nResult<=0 )
	{		
		printf("Err, CRouteServerTCP::Recv Head Or Close Order:%d\n", WSAGetLastError());				
		goto recv_close;
	}

	MsgBaseHead* pMsgHead = (MsgBaseHead*)BufferRecv;
	
	//
	//check head
	if( !ProtocolVerify.IsMsgSize(pMsgHead->nSizeOfMsg, 0, 0)
	 || !ProtocolVerify.IsMsgAction(pMsgHead->__nActionOrder) )
	{
		printf("收到不合法数据包!\n");		
		goto recv_close;
	}

	//
	//recv content with protocol
	nResult = RecvnTCP(nSocket, BufferRecv+name_msg_protocol::MSG_HEAD_BASE_SIZE, pMsgHead->nSizeOfMsg-name_msg_protocol::MSG_HEAD_BASE_SIZE);
	if( nResult<=0 )
	{
		printf("Err, CRouteServerTCP::Recv Content:%d\n", WSAGetLastError());		
		goto recv_close;
	}

	CUserBridge UserBridge;

	InitUserBridge(&UserBridge, nSocket);

	if( -1==g_WorldRoute.ResolveMsg(pMsgHead, &UserBridge) )
	{
		printf("Err, CRouteServerTCP::g_WorldRoute.ResolveMsg\n");
		goto recv_close;
	}

	return 0;

recv_close:
	Close();
	g_WorldRoute.CallBackClose( nSocket );
	return -1;
}

void CServerRouteTCP::Close()
{
	closesocket(nSocket);
	bIsConnect = false;
}

void CServerRouteTCP::CallBackClose()
{
	Close();
}

//
//CServerRouteThread
//
void CServerRouteThread::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );	
}

unsigned int CServerRouteThread::ThreadStartAddr(void *pArguments)
{	
	printf("CServerRouteThread::ThreadStartAddr:start\n");
	CServerRouteTCP *pRouteClientTCP = (CServerRouteTCP*)pArguments;

	while( g_bQuit!=true )
	{
		//更新的间隔时间
		Sleep(1000);

		if( false==pRouteClientTCP->bIsConnect )
		{
			pRouteClientTCP->Connect();
			
			continue;
		}		

		pRouteClientTCP->UpdatePeopleToRoute();

		pRouteClientTCP->Recv();

	}
	
	printf("CServerRouteThread::ThreadStartAddr:end\n");	
	return 0;	
}


//
//CServerRoute
//
bool CServerRoute::Init()
{

	return true;
}

void CServerRoute::Start()
{
	ServerRouteThread.Start(&ServerRouteTCP);
}