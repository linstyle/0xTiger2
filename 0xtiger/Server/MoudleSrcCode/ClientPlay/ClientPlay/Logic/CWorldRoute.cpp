#include "CWorldRoute.h"

CWorldRoute WorldRoute;


CWorldRoute::RESOLVE_MSG CWorldRoute::ResoleveFn[] = 
{
	&CWorldRoute::HelloWorld,
	&CWorldRoute::__FillFunc,
	&CWorldRoute::AskEncryption,	
};


int CWorldRoute::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{		
	return (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);
}

int CWorldRoute::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("It's no my Protocol!, Protocol OrderAction is:%d", pMsgBase->__nActionOrder);		
	return 0;
}


int  CWorldRoute::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgSayHello *pMsgSayHello = (MsgSayHello *)pMsgBase;

	printf("Warning, HelloWorld:%s\n", pMsgSayHello->Buffer);

	/*
		处理后返回,如果是客户端不做返回
	*/
	return nResult;
}

int CWorldRoute::AskEncryption(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	CUserBridgeNet  *pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic  *pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgClientAskEncryption *pAskEncryption = (MsgClientAskEncryption *)pMsgBase;

	pUserBridgeLogic->pLoginInfo->nIP = pAskEncryption->_nIP;
	pUserBridgeLogic->pLoginInfo->nPort = pAskEncryption->_nPort;

	return 0;
}