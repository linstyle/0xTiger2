#include "CRoutePlayUDP.h"

#include "../Logic/CWorldPlay.h"

extern bool g_bQuit;
extern CWorldPlay g_WorldPlay;

//
//debug tracer
//
void CRoutePlayUDP::TracerMe()
{
	printf("CRoutePlayUDP:TracerMe---------------------\n");
	printf("Listen:ports=%d,	ip=%s\n", nPort, inet_ntoa( *( (in_addr*)&nIP) ));	
}



//
//construct
//
CRoutePlayUDP::CRoutePlayUDP()
{
	nIdenti = -1;

	ProtocolVerify.SetVersion1(name_playmsg_protocol::PLAY_ORADER_ACTION_MAX);
}

CRoutePlayUDP::~CRoutePlayUDP()
{

}

void CRoutePlayUDP::Close(int nNetKey)
{
	
}

//
//public
//
bool CRoutePlayUDP::Init(int nObjectOfIndex)
{
	bool bResult=false;

	nIdenti = nObjectOfIndex;
	ReadFromConfigManager(nObjectOfIndex);
	InitSocketUDPS();

	TracerMe();

	return bResult;
}


//
//private
//
void CRoutePlayUDP::ReadFromConfigManager(int nIndex)
{
	CConfigManager::ReadRouteUDPListen(nIndex, &nPort, &nIP);
}

int CRoutePlayUDP::Recv()
{
	CUserBridge UserBridge;
	CUserBridgeNet  *pUserBridgeNet = &UserBridge.UserBridgeNet;
	CUserBridgeLogic  *pUserBridgeLogic = &UserBridge.UserBridgeLogic;

	int nResult, nSenderAddrSize = sizeof(UserBridge.UserBridgeNet.SenderAddr);

	nResult = RecvnUDP(nSocket, BufferRecv, name_msg_protocol::SOCKET_BUFF_SIZE, 0, (sockaddr *)&pUserBridgeNet->SenderAddr);
	if( -1==nResult )
	{		
		return -1;
	}

	bool bVerify = false;
	MsgBaseHead* pMsgBaseHead = (MsgBaseHead*)BufferRecv;

	//
	//UDP是数据包格式，需要确认收到的包长度
	if( nResult>=name_msg_protocol::MSG_HEAD_BASE_SIZE )
	{
		bVerify = ProtocolVerify.IsMsgSize( pMsgBaseHead->nSizeOfMsg, nResult, nResult) 
			|| ProtocolVerify.IsMsgAction( pMsgBaseHead->__nActionOrder );
	}

	if( false==bVerify )
	{		
		printf("CRoutePlayUDP::Recv():收到不合法数据包!");
		return 0;		
	}

	//
	//交给世界处理.复杂的逻辑中要先交给优先队列

	pUserBridgeNet->nSocketSend = this->nSocket;
	g_WorldPlay.ResolveMsg(pMsgBaseHead, &UserBridge);

	return 0;
}

//
//CRoutePlayUDPThread
//
unsigned int CRoutePlayUDPThread::ThreadStartAddr(void *pArguments)
{
	CRoutePlayUDP *pRouteUDP = (CRoutePlayUDP*)pArguments;

	printf("CRoutePlayUDPThread::ThreadStartAddr SerialNumber:%d start!\n", pRouteUDP->GetIdenti());	

	while( g_bQuit!=true )
	{
		if( -1==pRouteUDP->Recv() )
		{			
			printf("Err, CRoutePlayUDP::Recv:%d \n", WSAGetLastError());
		}		
	}

	printf("CRoutePlayUDPThread::ThreadStartAddr SerialNumber:%d quit!\n", pRouteUDP->GetIdenti());	
	
	return 0;
}

void CRoutePlayUDPThread::Start(void *pArguments)
{
	//
	//一开始时睡眠状态
	hThreadSelf = (HANDLE)_beginthreadex(NULL, 0, ThreadStartAddr, pArguments, CREATE_SUSPENDED, &idThreadSelf);
	MTVERIFY( 0!=hThreadSelf );		
}

int CRoutePlayUDPThread::_ResumeThread()
{
	return ResumeThread(hThreadSelf);
}

int CRoutePlayUDPThread::_SetThreadIdealProcessor( int nProcessorOfIndex )
{
	return SetThreadIdealProcessor(hThreadSelf, nProcessorOfIndex);
}

//
//CRoutePlayUDP
//
CRoutePlay::~CRoutePlay()
{
	delete []pRoutePlayUDPThread;
	delete []pRoutePlayUDP;
}

bool CRoutePlay::Init( int nThreadOfNumber )
{	
	pRoutePlayUDP = new CRoutePlayUDP[nThreadOfNumber];
	pRoutePlayUDPThread = new CRoutePlayUDPThread[nThreadOfNumber];
	for(int i=0; i<nThreadOfNumber; ++i)
	{
		pRoutePlayUDP[i].Init(i);
	}
	
	return true;
}

void CRoutePlay::Start( int nThreadOfIndex )
{
	pRoutePlayUDPThread[nThreadOfIndex].Start( &pRoutePlayUDP[nThreadOfIndex] );	
}
