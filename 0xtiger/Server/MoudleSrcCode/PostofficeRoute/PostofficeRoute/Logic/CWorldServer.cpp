#include "CWorldServer.h"

CWorldServer g_WorldServer;


CWorldServer::RESOLVE_MSG CWorldServer::ResoleveFn[] = 
{		
	&CWorldServer::HelloWorld,	/*作为一个S端，需要进行协议解析, 并且返回*/
	&CWorldServer::ServerLogin,
	&CWorldServer::UpdateRouteServerPeople
};

int CWorldServer::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{		
	/*
		获取到逻辑对象
	*/
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	pUserBridgeLogic->pMRole = MRoleManager.GetMRoleByNetKey( pUserBridgeNet->nSocketSend );

	if( NULL==pUserBridge->UserBridgeLogic.pMRole )
	{
		printf("Failed, CWorldServer::ResolveMsg:Get 'NULL' of LogicElement from hash set\n");
		return -1;
	}

	int nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);

	if( -1==nResult )
	{
		Close(pUserBridge);
	}
	
	return nResult;
}

CWorldServer::CWorldServer()
{
}


CWorldServer::~CWorldServer()
{
}

int CWorldServer::TCPSend( MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	nResult = CCommonSocket::SendnTCP(pUserBridgeNet->nSocketSend, (const char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg);
	
	return nResult;
}

void CWorldServer::CallBackTracerMe()
{
	printf("CWorldServer::CallBackTracerMe---------------------\n");
	printf("MRoleManager Sum Use:%d\n", MRoleManager.GetMRoleSumUse());
	printf("MRoleManager Sum Free:%d\n", MRoleManager.GetMRoleSumFree());
}


void CWorldServer::Close(CUserBridge* pUserBridge)
{
	MRoleManager.MRoleErase( pUserBridge->UserBridgeNet.nSocketSend ) ;
	printf("Warning, CWorldServer::Close:OK:%d", pUserBridge->UserBridgeNet.nSocketSend);
}

void CWorldServer::CallBackClose(int nNetKey)
{
	MRoleManager.MRoleErase( nNetKey );
	printf("Warning, CWorldServer::CallBackClose:OK:%d\n", nNetKey);
}


int CWorldServer::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgSayHello *pMsgSayHello = (MsgSayHello *)pMsgBase;

	printf("Warning, HelloWorld:%s\n", pMsgSayHello->Buffer);

	/*
		处理后返回
	*/
	char *p = pMsgSayHello->Buffer+strlen(pMsgSayHello->Buffer);
	strcpy(p, "Yeah! I have receive your 'say hello'--- PostofficeRoute");

	nResult = TCPSend(pMsgBase, pUserBridge);
	if( -1==nResult )
	{
		printf("Err, CWorldServer::TCPSend:%d \n", WSAGetLastError());
	}

	return nResult;
}

int CWorldServer::ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgServerLogin *pMsgServerLogin = ( MsgServerLogin* )&pMsgBase;
	
	printf("Warning, The (%d) Number PostofficeServer Login! \n", pMsgServerLogin->nBinIdenti);

	/*
		分配逻辑对象,并且绑定
	*/
	if( NULL == MRoleManager.MRoleAdd(pUserBridgeNet->nSocketSend) )
	{
		return -1;
	}

	return 0;

}

int CWorldServer::UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	MsgServerUpdatePeople *pMsgServerUpdate = (MsgServerUpdatePeople *)pMsgBase;

	if( pMsgServerUpdate->nBinIdenti>=CConfigManager::GetMaxConnectItem() )
	{
		printf("Err, CWorldServer::UpdateRouteServerPeople:nBinIdenti=%d \n", pMsgServerUpdate->nBinIdenti);
		return -1;
	}

	SERVER_INFO ServerUpdate;
	SERVER_INFO *pServerRand = g_RouteRand.GetServerObject(pMsgServerUpdate->nBinIdenti);
	
	ServerUpdate.nEnable = true;
	ServerUpdate.nIP = pMsgServerUpdate->nIP;
	ServerUpdate.nPort = pMsgServerUpdate->nPort;
	ServerUpdate.nSumPeople = pMsgServerUpdate->nPeople;		
	
	memcpy(pServerRand, &ServerUpdate, sizeof(SERVER_INFO) );

	g_RouteRand.CtrlProportion();

	return 0;
}




