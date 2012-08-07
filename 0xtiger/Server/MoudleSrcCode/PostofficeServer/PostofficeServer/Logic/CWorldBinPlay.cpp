#include "CWorldBinPlay.h"

CWorldBinPlay g_WorldBinPlay;

//
//
//public
CWorldBinPlay::RESOLVE_MSG CWorldBinPlay::ResoleveFn[] = 
{
	&CWorldBinPlay::HelloWorld,		/*服务端，需要进行返回*/
	&CWorldBinPlay::ServerLogin,
	&CWorldBinPlay::Test	
};

CWorldBinPlay::CWorldBinPlay()
{
	
	
}

CWorldBinPlay::~CWorldBinPlay()
{
	
}

int CWorldBinPlay::Close(CUserBridge* pUserBridge)
{
	return CallBackClose(pUserBridge);
}

int CWorldBinPlay::CallBackClose(CUserBridge* pUserBridge)
{	
	return MRoleManager.MRoleErase( pUserBridge->UserBridgeNet.nInNetPoolRes);
}

int CWorldBinPlay::CallBackClose(int nIdenti)
{
	return MRoleManager.MRoleErase( nIdenti );
}

void CWorldBinPlay::CallBackTracerMe()
{
	printf("\nCWorldBinPlay::CallBackTracerMe\n");
	printf("MRoleManager Sum Use:%d\n", MRoleManager.GetMRoleSumUse());
	printf("MRoleManager Sum Free:%d\n", MRoleManager.GetMRoleSumFree());
	printf("\n");
	RouteTableManager.CallBackTracerMe();
}

void CWorldBinPlay::FillSendPack(MsgPostHead* pMsgPostHead, CUserBridge* pUserBridge)
{
	CMRole* pMRole = pUserBridge->UserBridgeLogic.pMRole;
	//pMsgPostHead->nInSocket = pMRole->
}

void CWorldBinPlay::InitUserBridge(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	/*
		先进行一个脱壳，修改size大小，并且初始化一个对象套接字
	*/
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	MsgPostHead* pMsgPostHead = (MsgPostHead*)((int)pMsgBase + pMsgBase->nSizeOfMsg - sizeof(MsgPostHead));

	pMsgBase->nSizeOfMsg = pMsgBase->nSizeOfMsg - sizeof(MsgPostHead);
	pUserBridgeNet->nInNetToSocket = pMsgPostHead->nInSocket;
}

//int CWorldBinPlay::MRoleInfoToLogic(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
//{
//	MsgMRoleInfoToLogic *pMsgToLogic = (MsgMRoleInfoToLogic *)pMsgBase;
//	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
//	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
//
//	pMsgToLogic->nIdentiInPostoffice = CConfigManager::GetGlobalIdenti() ;
//	pMsgToLogic->nResIdentiInPostoffice= pUserBridge->UserBridgeNet.nInNetPoolRes;
//	pMsgToLogic->nInPostSocket = pUserBridgeNet->nMRoleSocket;
//
//	if( -1==TCPSend(pMsgBase, pUserBridge) )
//	{
//		printf("CWorldBinPlay::MRoleInfoToLogic:%d\n", WSAGetLastError());		
//		return -1;
//	}	
//}
int CWorldBinPlay::Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	switch (pMsgBase->__nActionDo)
	{
	case 1:
		nResult = Test2(pMsgBase, pUserBridge);
		break;

	default:
		nResult = __FillFunc(pMsgBase, pUserBridge);
	}

	return nResult;
}

int CWorldBinPlay::UpdateTest1(CUserBridge* pUserBridge)
{
	pUserBridge->UserBridgeLogic.pMRole = MRoleManager.GetMRoleElementByIdenti( pUserBridge->UserBridgeNet.nInNetPoolRes );
	CMRole* pMRole = pUserBridge->UserBridgeLogic.pMRole;
	MsgUpdateTest1 MsgT1;

	MsgT1.nIdentiInPostoffice = CConfigManager::GetGlobalIdenti();
	MsgT1.nResIdentiInPostoffice = pUserBridge->UserBridgeNet.nInNetPoolRes;
	MsgT1.nInPostSocket = pUserBridge->UserBridgeNet.nSocket;

	//debug
	printf("CWorldBinPlay::UpdateTest1 socket:%d\n", MsgT1.nInPostSocket);
	//end debug

	pUserBridge->UserBridgeNet.nSocket = RouteTableManager.GetBinSocketByIdenti(0, 0);

	if( -1==TCPSend(&MsgT1, pUserBridge) )
	{
		printf("CWorldBinPlay::MsgTest:%d\n", WSAGetLastError());		
		return -1;
	}

	
	return 0;
}

int CWorldBinPlay::Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	if( -1==UpdateTest1(pUserBridge) )
	{
		return -1;
	}

	return 0;
}

int CWorldBinPlay::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nMRoleID = pUserBridge->UserBridgeNet.nInNetPoolRes;
	pUserBridge->UserBridgeLogic.pMRole = MRoleManager.GetMRoleElementByIdenti( nMRoleID );

	if( NULL==pUserBridge->UserBridgeLogic.pMRole )
	{
		printf("Err, CWorldBinPlay::ResolveMsg:NULL==GetMRole(), nMRoleID:%d\n", nMRoleID);
		return -1;
	}

	int nResult;
	switch (pMsgBase->nRoutePriority)
	{
	case 0:
		nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);		
		break;

	default:		
		nResult = RouteForward(pMsgBase, pUserBridge);		
	}

	if( -1==nResult )
	{
		if( -1==Close(pUserBridge) )
		{
			printf("Failed, CWorldBinPlay::ResolveMsg:Close()\n");
		}
		printf("Warning, CWorldBinPlay::ResolveMsg:Close()\n");
	}

	return nResult;
}


int CWorldBinPlay::TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge )
{
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	return CCommonSocket::SendnTCP(pUserBridgeNet->nSocket, (const char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg);
}

int CWorldBinPlay::TCPPackSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge)
{
	/*
		填充要携带的协议包，修改大小，最后发送
	*/
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	MsgPostHead *pMsgPostHead = (MsgPostHead*)pSendMsgBase+pSendMsgBase->nSizeOfMsg;

	FillSendPack( pMsgPostHead, pUserBridge);

	return CCommonSocket::SendnTCP(pUserBridgeNet->nSocket, (const char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg);
}

//
//
//private
int CWorldBinPlay::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("Err, It's no my Protocol!, Protocol ActionOrder:%d, ActionDo:%d\n", pMsgBase->__nActionOrder, pMsgBase->__nActionDo);
	return -1;
}


/*
	__nActionOrder = 0
	__nActionDo = 0
*/
int CWorldBinPlay::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
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
	strcpy(p, "Yeah! I have receive your 'say hello'--- PostofficeServer");

	nResult = TCPSend(pMsgBase, pUserBridge);
	if( -1==nResult )
	{
		printf("Err, CWorldBinPlay::TCPSend:%d \n", WSAGetLastError());
	}

	return nResult;
}

int CWorldBinPlay::ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	/*
		0：bin服务器登陆
		1：dpc服务器登陆
	*/
	int nResult;
	switch (pMsgBase->__nActionDo)
	{
	case 0:
		nResult = ServerLoginBin(pMsgBase, pUserBridge);
		break;

	case 1:
		nResult = ServerLoginDpc(pMsgBase, pUserBridge);
		break;

	default:
		printf("Err, CWorldBinPlay::ServerLogin not case\n");
		__FillFunc(pMsgBase, pUserBridge);
		nResult = -1;
		break;
	}

	return nResult;
}


/*
	__nActionOrder = 1
	__nActionDo = 0
*/
int CWorldBinPlay::ServerLoginBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	MsgServerLoginBin *pMsgLoginBin = (MsgServerLoginBin*)pMsgBase;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	/*
		将对象添加到路由表中，并且将该对象的逻辑权限提升
	*/

	int nResult;

	nResult = RouteTableManager.BinAdd(pMsgLoginBin->nLineIdenti, pMsgLoginBin->nBinIdenti, pUserBridgeNet->nSocket);

	if( -1==nResult )
	{	
		printf("Failed, CWorldBinPlay::BinServerLogin:RouteTableManager.ServerAdd !!!\n");
		return -1;	
	}

	pUserBridgeLogic->pMRole->MRoleHead.SetMRoleLevel( name_mrole_head::IDENTI_BIN );

	printf("Warning, CWorldBinPlay::BinServerLogin:Ok. IP = %s		Port=%d\n", 
			inet_ntoa(pUserBridgeNet->SenderAddr.sin_addr), ntohs(pUserBridgeNet->SenderAddr.sin_port)
		);

	return 0;
}

/*
	__nActionOrder = 1
	__nActionDo = 1
*/
int CWorldBinPlay::ServerLoginDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{
	MsgServerLoginDpc *pMsgLoginDpc = (MsgServerLoginDpc*)pMsgBase;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	/*
		将对象添加到路由表中，并且将该对象的逻辑权限提升
	*/

	int nResult;
	nResult = RouteTableManager.DpcAdd(pUserBridgeNet->nSocket);

	if( -1==nResult )
	{	
		printf("Failed, CWorldBinPlay::ServerLoginDpc:RouteTableManager.ServerAdd !!!\n");
		return -1;	
	}

	pUserBridgeLogic->pMRole->MRoleHead.SetMRoleLevel( name_mrole_head::IDENTI_BIN );

	printf("Warning, CWorldBinPlay::DpcServerLogin:Ok. IP = %s		Port=%d\n", 
			inet_ntoa(pUserBridgeNet->SenderAddr.sin_addr), ntohs(pUserBridgeNet->SenderAddr.sin_port)
		);

	return 0;
}

int CWorldBinPlay::RouteForward( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{
	int nResult;
	
	/*
		1:bin转发命令
		2:dpc转发命令
		3:client转发命令
	*/
	switch (pMsgBase->nRoutePriority)
	{
	case 1:
		nResult = RouteForwardBin(pMsgBase, pUserBridge);
		break;

	case 2:
		nResult = RouteForwardDpc(pMsgBase, pUserBridge);
		break;

	case 3:
		InitUserBridge(pMsgBase, pUserBridge);
		nResult = RouteForwardClient(pMsgBase, pUserBridge);
		break;

	case 4:
		nResult = __FillFunc(pMsgBase, pUserBridge);
	}

	return nResult;

}

int CWorldBinPlay::RouteForwardBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	CUserRouteNavi *pUserNavi= &pUserBridgeLogic->pMRole->MRoleHead.UserRouteNavi;		
	int nBinSocket = RouteTableManager.GetBinSocketByIdenti(pUserNavi->GetIdentiLine(), 
															pUserNavi->GetIdentiBin());

	if( -1==nBinSocket )
	{
		printf("Failed, CWorldBinPlay::RouteForwardBin:GetBinSocketByIdenti. Line:%d, BinIdenti:%d\n", 
				pUserNavi->GetIdentiLine(), pUserNavi->GetIdentiBin());
		return 0;
	}

	int nResult;

	nResult = CCommonSocket::SendnTCP(nBinSocket, (const char*)pMsgBase, pMsgBase->nSizeOfMsg);
	if( -1==nResult )
	{		
		printf("Err, CWorldBinPlay::RouteForwardBin TCPSend err:%d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}

int CWorldBinPlay::RouteForwardDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	CUserRouteNavi *pUserNavi = &pUserBridgeLogic->pMRole->MRoleHead.UserRouteNavi;		
	int nDpcSocket = RouteTableManager.GetDpcSocket();

	if( -1==nDpcSocket )
	{
		printf("Failed, CWorldBinPlay::RouteForwardBin:GetDpcSocket\n");
		return 0;
	}

	int nResult;
	nResult = CCommonSocket::SendnTCP(nDpcSocket, (const char*)pMsgBase, pMsgBase->nSizeOfMsg);
	if( -1==nResult )
	{		
		printf("CWorldBinPlay::RouteForwardDpc :TCPSend err:%d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}


int CWorldBinPlay::RouteForwardClient( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge )
{
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;

	int nResult;
	int nClientSocket = pUserBridgeNet->nInNetToSocket;
	//debug
	printf("CWorldBinPlay::RouteForwardClient socket:%d\n", nClientSocket);
	//end debug
	nResult = CCommonSocket::SendnTCP(nClientSocket, (const char*)pMsgBase, pMsgBase->nSizeOfMsg);
	if( -1==nResult )
	{		
		printf("CWorldBinPlay::RouteForwardClient :TCPSend err:%d\n", WSAGetLastError());
		return -1;
	}

	return 0;
}


