#include "CBinServerPlayTCP.h"
#include "../CConfigManager.h"
#include "../Logic/CWorldServer.h"

extern volatile bool g_bQuit;
extern CWorldServer g_WorldServer;

//
//public
//
CBinServerPlayTCP::CBinServerPlayTCP()
{
	bIsConnect = false;
	bIsLoginServer = false;

	ProtocolVerify.SetVersion1(name_bpmsg_protocol::BP_ORADER_ACTION_MAX);	
}

CBinServerPlayTCP::~CBinServerPlayTCP()
{

}

void CBinServerPlayTCP::TracerMe()
{
	printf("\nCBinServerPlayTCP:TracerMe\n");
	printf("Identi:%d	Connect:Port=%d		ip=%s\n", nConnectPostofficeIndex, nPort, inet_ntoa( *( (in_addr*)&nIP) ));	
}

void CBinServerPlayTCP::Init()
{
	ReadFromConfigManager();
	TracerMe();	
}

//
//private
//
void CBinServerPlayTCP::ReadFromConfigManager()
{
	CConfigManager::ReadConnectPostofficeServer(nConnectPostofficeIndex, &nPort, &nIP);
}

int CBinServerPlayTCP::LoginServer()
{
	MsgServerLoginBin MsgBinLogin;

	MsgBinLogin.nRoutePriority = 0;
	MsgBinLogin.nLineIdenti = CConfigManager::GetLineIdenti();
	MsgBinLogin.nBinIdenti = CConfigManager::GetGlobalIdenti();
	
	
	if( -1==Send(&MsgBinLogin) )
	{		
		printf("Err,CRouteClientTCP::LoginServer:%d\n", WSAGetLastError());		
		return -1;
	}

	//
	//bin主动等待routeserver发送消息。无需再等待验证是否成功的返回
	bIsLoginServer = true;
	return 0;
}

void CBinServerPlayTCP::Connect()
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
		printf("Err, Indenti:%d   CRouteClientTCP::ThreadStartAddr:Connect:%d\n", nConnectPostofficeIndex, WSAGetLastError());
		Close();
		return;
	}

	printf("Warning, CRouteClientTCP::ThreadStartAddr:Connect:ok\n");	
	bIsConnect = true;

	SayHelloWorld();	
}

int CBinServerPlayTCP::Send(MsgBaseHead* pMsgBaseHead)
{	
	int nResult;

	nResult = SendnTCP(nSocket, (const char*)pMsgBaseHead, pMsgBaseHead->nSizeOfMsg);
	if( nResult<=0 )
	{
		Close();		
		return -1;
	}

	return 0;
}

/*
	Recv需要多次接收(头+体)，并且验证合法性。
	因此把资源操作放在外部，而消息提示放在内部 
*/
int CBinServerPlayTCP::Recv()
{
	int nResult;
	CUserBridge    UserBridge;		//防止goto 错误提示

	//debug, with select
	fd_set SetRead;
	int nTotal = 0;
	timeval TimeSelect;

	FD_ZERO(&SetRead);
	FD_SET(nSocket, &SetRead);
	TimeSelect.tv_sec=1;
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
		printf("Err, CBinServerPlayTCP::Recv Head Or Close Order:%d\n", WSAGetLastError());
		goto recv_close;
	}

	MsgBaseHead* pMsgHead = (MsgBaseHead*)BufferRecv;

	//
	//check head
	if( !ProtocolVerify.IsMsgSize(pMsgHead->nSizeOfMsg, 0, 0)
	 || !ProtocolVerify.IsMsgAction(pMsgHead->__nActionOrder) )
	{				
		printf("Err, 收到不合法数据包!\n");	
		goto recv_close;
	}

	//
	//recv content with protocol
	nResult = RecvnTCP(nSocket, BufferRecv+name_msg_protocol::MSG_HEAD_BASE_SIZE, pMsgHead->nSizeOfMsg-name_msg_protocol::MSG_HEAD_BASE_SIZE);
	if( nResult<=0 )
	{		
		printf("Err, CBinServerPlayTCP::Recv Content:Close a socket:%d\n", WSAGetLastError());
		goto recv_close;
	}

	InitUserBridge(&UserBridge, nSocket);
	if( -1==g_WorldServer.ResolveMsg(pMsgHead, &UserBridge) )
	{
		printf("Err, CBinServerPlayTCP::g_WorldServer.ResolveMsg\n");
		goto recv_close;
	}
	return 0;

recv_close:
	Close();
	return -1;
}

void CBinServerPlayTCP::Close()
{
	closesocket(nSocket);
	bIsConnect = false;
	bIsLoginServer = false;
}

void CBinServerPlayTCP::SayHelloWorld()
{
	MsgSayHello HelloWorld;	

	strcpy(HelloWorld.Buffer, "ServerBin Say: Hello!");

	if( -1==Send(&HelloWorld) )
	{
		printf("Err, CBinServerPlayTCP::SayHelloWorld:%d\n", WSAGetLastError());
	}
}

void CBinServerPlayTCP::InitUserBridge(CUserBridge *pUserBridge, int nNetKey)
{
	pUserBridge->UserBridgeNet.nSocket = nNetKey;
}
//
//
//CBinServerPlayThread

//
//public
void CBinServerPlayThread::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );	
}


unsigned int CBinServerPlayThread::ThreadStartAddr(void *pArguments)
{	
	printf("CBinServerPlayTCP::ThreadStartAddr:start\n");

	CBinServerPlayTCP *pBinServerPlay = (CBinServerPlayTCP*)pArguments;
	int nMaxSecenCount = g_WorldServer.SceneManager.GetCount();
	int nMaxPostofficeCount = CConfigManager::GetMaxPostofficeCount();

	//debug
	g_WorldServer.SceneManager.GetScene(0)->MRoleAdd();
	//end debug
	while( g_bQuit!=true )
	{
		int i;
		/*
			对网关收发的遍历
		*/
		for(i=0; i<nMaxPostofficeCount; ++i)
		{
			if( false==pBinServerPlay[i].bIsConnect )
			{				
				pBinServerPlay[i].Connect();
				continue;
			}

			if( false==pBinServerPlay[i].bIsLoginServer )
			{
				pBinServerPlay[i].LoginServer();
				continue;
			}		

			pBinServerPlay[i].Recv();		
		}

		/*
			一定频率后，对场景的遍历
		*/
		for(i=0; i<nMaxSecenCount; ++i)
		{
			g_WorldServer.SceneManager.GetScene(i)->CallBackDoing();
		}


		Sleep(1000);
	}
	
	printf("CBinServerPlayTCP::ThreadStartAddr:end");
	return 0;
}

//
//CBinServerPlay
//
CBinServerPlay::CBinServerPlay()
{
	pBinServerPlayTCP = new CBinServerPlayTCP[ CConfigManager::GetMaxPostofficeCount() ];
	for(int i=0; i<CConfigManager::GetMaxPostofficeCount(); ++i)
	{
		pBinServerPlayTCP[i].nConnectPostofficeIndex = i;
		pBinServerPlayTCP[i].Init();
	}
}

CBinServerPlay::~CBinServerPlay()
{
	//跟main中的WSACleanup()冲突
	delete []pBinServerPlayTCP;

}

void CBinServerPlay::Start()
{
	BinServerPlayThread.Start(pBinServerPlayTCP);
}

bool CBinServerPlay::Init()
{
	
	return true;
}

void CBinServerPlay::Release()
{
	delete []pBinServerPlayTCP;
}
