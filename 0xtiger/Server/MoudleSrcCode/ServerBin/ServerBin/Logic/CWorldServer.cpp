#include "CWorldServer.h"

#include "../Standalone/GlobalRes/CGlobalResMRole.h"
extern CGlobalResMRole GlobalResMRole;

CWorldServer g_WorldServer;

CWorldServer::RESOLVE_MSG CWorldServer::ResoleveFn[] = 
{
	&HelloWorld,		/*客户端，接受者，不做反馈*/
	&__FillFunc,
	&Test
};

CWorldServer::CWorldServer()
{
	
	
}

CWorldServer::~CWorldServer()
{
	
}

int CWorldServer::TCPSend(CUserBridge* pUserBridge, MsgBaseHead *pSendMsgBase)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	nResult = CCommonSocket::SendnTCP(pUserBridgeNet->nSocket, (const char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg);
	if( -1==nResult )
	{		
		Close(pUserBridgeLogic->pMRole);
		return -1;
	}

	return 0;
}

void CWorldServer::Close(CMRole *pMRole)
{
	CScene* pScene = SceneManager.GetScene( pMRole->MRoleHead.InScene.nWhereIdenti);
	
	pScene->MRoleManager.MRoleErase(pMRole, 1);
}

void CWorldServer::FillPackBuffer(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge, int nMsgBaseOffset)
{
	printf("CWorldServer::FillPackBuffer: \n");
	printf("1---nSizeOfMsg, nMsgBaseOffset:%d\n", pMsgBase->nSizeOfMsg, nMsgBaseOffset);

	MsgPostHead *pMsgPostHead = (MsgPostHead*)((int)pMsgBase + nMsgBaseOffset);
	CMRole *pMRole = pUserBridge->UserBridgeLogic.pMRole;

	pMsgPostHead->nInSocket = pMRole->MRoleHead.InPostoffice.nSocket;
	pMsgBase->nSizeOfMsg += sizeof(MsgPostHead);

	printf("2---socket:%d, size:%d\n", pMsgPostHead->nInSocket, pMsgBase->nSizeOfMsg);
}

int CWorldServer::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;

	//debug
	pUserBridge->UserBridgeLogic.pMRole = GlobalResMRole.m_MRoleList.GetUseElementAtID(pMsgBase->nInBinPoolRes);
	
	//end debug

	/*
		脱包
	*/
	nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);
	if( -1==nResult )
	{
		Close(pUserBridge->UserBridgeLogic.pMRole);
		printf("Warning, CWorldServer::ResolveMsg:Close()\n");
	}

	return nResult;
}


int CWorldServer::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("It's no my Protocol!, Protocol OrderAction is:%d", pMsgBase->__nActionOrder);	
	return -1;
}

int CWorldServer::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgSayHello *pMsgSayHello = (MsgSayHello *)pMsgBase;

	printf("Warning, HelloWorld:%s\n", pMsgSayHello->Buffer);

	return 0;
}

int CWorldServer::Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("-------------CWorldServer::Test\n");
	int nResult;

	switch (pMsgBase->__nActionDo)
	{
	case 0:
		nResult = Test1(pMsgBase, pUserBridge);
		break;

	case 2:
		nResult = Test2(pMsgBase, pUserBridge);
		break;

	default:
		printf("Warning, deault\n");
		nResult = __FillFunc(pMsgBase, pUserBridge);
	}

	return nResult;
}

int CWorldServer::Test1(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CMRole* pMRole = pUserBridgeLogic->pMRole;

	MsgUpdateTest1 *pMsgTest1 = (MsgUpdateTest1 *)pMsgBase;

	pMRole->MRoleHead.InPostoffice.nSocket = pMsgTest1->nInPostSocket;

	printf("Warning, CWorldServer::Test1\n");

	return 0;
}

int CWorldServer::Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;
	CMRole* pMRole = pUserBridgeLogic->pMRole;	

	MsgTest3 *pMsgTest3 = (MsgTest3 *)pMsgBase;

	FillPackBuffer(pMsgBase, pUserBridge, sizeof(MsgTest3));
	printf("Warning, CWorldServer::Test2, money:%d\n", pMsgTest3->nMoney);

	pMsgTest3->nRoutePriority = 3;
	pMsgTest3->nMoney += 1000;


	nResult = TCPSend(pUserBridge, pMsgBase);
	if( -1==nResult )
	{
		printf("Err, CWorldServer::Test2:%d\n", WSAGetLastError());
	}

	return nResult;
}