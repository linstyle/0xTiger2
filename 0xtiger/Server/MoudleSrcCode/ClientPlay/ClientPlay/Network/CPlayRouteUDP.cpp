#include "CPlayRouteUDP.h"
#include "../CConfigManager.h"
#include "../Logic/CWorldRoute.h"
extern CWorldRoute WorldRoute;

extern volatile bool g_bQuit;
//
//
//public
void CPlayRouteUDP::TracerMe()
{
	printf("CPlayRouteUDP:TracerMe---------------------\n");
	printf("Connect:ports=%d,	ip=%s\n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));
}

CPlayRouteUDP::CPlayRouteUDP()
{
	ReadFromConfigManager();
	TracerMe();

	InitSocketUDPC();

	bGetLoginInfo = false;

	PublicProtocolVerify.SetVersion1(name_playmsg_protocol::PLAY_ORADER_ACTION_MAX);
}

CPlayRouteUDP::~CPlayRouteUDP()
{

}

bool CPlayRouteUDP::GetbGetLoginInfo()
{
	return bGetLoginInfo;
}

void CPlayRouteUDP::SetbGetLoginInfo(bool b)
{
	bGetLoginInfo = b;
}

LOGIN_INFO* CPlayRouteUDP::GetLoginInfo()
{
	return &LoginInfo;
}

//
//
//private
void CPlayRouteUDP::ReadFromConfigManager()
{
	CConfigManager::ReadClientLoginConnect(&nPort, &nIP);
}

int  CPlayRouteUDP::StartAskLoginInfo()
{
	MsgClientAskEncryption MsgAskEncryption;

	if( -1==Send(&MsgAskEncryption) )
	{
		printf("CPlayRouteUDP::Send():%d\n", WSAGetLastError());		
		return -1;
	}

	Sleep(100);
	
	if( -1==Recv() )
	{
		printf("CPlayRouteUDP::Recv():%d\n", WSAGetLastError());		
		return -1;
	}

	return 0;

}

int CPlayRouteUDP::Connect()
{

	return 0;
}

int CPlayRouteUDP::Send(MsgBaseHead* pMsgBaseHead)
{
	int nResult;

	nResult = SendnUDP(nSocket, (char*)pMsgBaseHead, pMsgBaseHead->nSizeOfMsg, 0, (sockaddr*)&Addr);
	
	return nResult;
}

int CPlayRouteUDP::Recv()
{
	int nTotal, nResult;	
	CUserBridge UserBridge;
	fd_set SetRead;
	timeval TimeSelect;

	TimeSelect.tv_sec=3;
	TimeSelect.tv_usec=0;
	FD_ZERO(&SetRead);
	FD_SET(nSocket, &SetRead);

	nTotal = select(0, &SetRead, NULL, NULL, &TimeSelect);
	if( nTotal<=0 )
	{
		printf("Err,CRoutePlayUDP::Recv():recv data timeout");		
		return -1;
	}

	nResult = RecvnUDP(nSocket, BufferRecv, name_msg_protocol::SOCKET_BUFF_SIZE, 0, (sockaddr*)&UserBridge.UserBridgeNet.SenderAddr);
	if( -1==nResult )
	{
		return -1;
	}

	bool bVerify=false;
	MsgBaseHead* pMsgBaseHead = (MsgBaseHead*)BufferRecv;
	if( nResult>name_msg_protocol::MSG_HEAD_BASE_SIZE )
	{
		bVerify = PublicProtocolVerify.IsMsgSize(pMsgBaseHead->nSizeOfMsg, nResult, nResult) 
			|| PublicProtocolVerify.IsMsgAction(pMsgBaseHead->__nActionDo);
	}
	if( false==bVerify )
	{		
		printf("CPlayRouteUDP::Recv():收到不合法数据包!\n");		
		return -1;
	}

	UserBridge.UserBridgeLogic.pLoginInfo = GetLoginInfo();
	WorldRoute.ResolveMsg(pMsgBaseHead, &UserBridge);

	return 0;
}

//
//CCPlayRouteUDPThread
//
unsigned int CPlayRouteUDPThread::ThreadStartAddr(void *pArguments)
{	
	printf("CCPlayRouteUDPThread::ThreadStartAddr:start!\n");

	CPlayRouteUDP *pPlayClientUDP = (CPlayRouteUDP*)pArguments;

	while( true!=g_bQuit)
	{		
		//
		//连续的取3次。
		for(int i=0; i<name_playclient_udp::TRY_GETLOGIN_MAX; ++i)
		{
			if( 0==pPlayClientUDP->StartAskLoginInfo() )
			{				
				pPlayClientUDP->SetbGetLoginInfo(true);
				goto ThreadStartAddr_End;
			}
			Sleep(1000);
		}
		goto ThreadStartAddr_End;
	}

ThreadStartAddr_End:	
	printf("CCPlayRouteUDPThread::ThreadStartAddr:end!\n");
	
	return 0;
}



void CPlayRouteUDPThread::Start(void *pArguments)
{
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, 0, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );	
}

//
//CPlayRoute
//
void CPlayRoute::Start()
{
	PlayRouteUDPThread.Start(&PlayRouteUDP);
}

bool CPlayRoute::Init()
{
	return true;
}