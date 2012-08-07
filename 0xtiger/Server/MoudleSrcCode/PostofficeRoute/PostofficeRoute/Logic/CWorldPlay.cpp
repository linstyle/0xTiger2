#include "CWorldPlay.h"
#include "../stdafx.h"
#include "0x_Network.h"
#include "../Standalone/CRouteRand.h"

extern CRouteRand g_RouteRand;

CWorldPlay g_WorldPlay;

CWorldPlay::RESOLVE_MSG CWorldPlay::ResoleveFn[] = 
{
	&CWorldPlay::__FillFunc,/*UDP²»ÐèÒªSay Hello*/
	&CWorldPlay::__FillFunc,
	&CWorldPlay::AskEncryption,	
};

int CWorldPlay::UDPSend(CUserBridgeNet *pUserBridgeNet, MsgBaseHead *pSendMsgBase)
{
	int nResult;

	nResult = CCommonSocket::SendnUDP(pUserBridgeNet->nSocketSend, (const char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg,
									  0, (SOCKADDR *) &pUserBridgeNet->SenderAddr);

	return nResult;
}

void CWorldPlay::Close(CUserBridge* pUserBridge)
{
	printf("Warning, CWorldServer::Close\n");
}

int CWorldPlay::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge *pUserBridge )
{
	int nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);

	if( -1==nResult )
	{
		Close(pUserBridge);
	}
	
	return nResult;
}

int CWorldPlay::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("It's no my Protocol!, Protocol OrderAction is:%d", pMsgBase->__nActionOrder);
	return -1;
}

int CWorldPlay::AskEncryption(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge)
{
	CUserBridgeNet  *pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic  *pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	const SERVER_INFO *pReServerInfo = g_RouteRand.GetRandObject();	
	
	MsgClientAskEncryption MsgAskEncryption;

	if( NULL!=pReServerInfo )
	{
		MsgAskEncryption._nIP = pReServerInfo->nIP;
		MsgAskEncryption._nPort = pReServerInfo->nPort;
	}
	
	printf("Disposal MsgClientAskEncryption ok\n");

	int nResult = UDPSend(pUserBridgeNet, &MsgAskEncryption);
	if( -1==nResult )
	{		
		printf("Err, CWorldPlay::AskEncryption:UDPSend:%d", WSAGetLastError());
	}

	return nResult;
}


