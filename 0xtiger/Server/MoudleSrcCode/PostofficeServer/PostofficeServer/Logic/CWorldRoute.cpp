
#include "CWorldRoute.h"
#include "0x_Network.h"

#include "CWorldBinPlay.h"
extern CWorldBinPlay g_WorldBinPlay;

CWorldRoute g_WorldRoute;


CWorldRoute::RESOLVE_MSG CWorldRoute::ResoleveFn[] = 
{
	&CWorldRoute::HelloWorld,	/*做为连接端，只需要解析出字符，不需要再次返回*/
	&CWorldRoute::__FillFunc,
	&CWorldRoute::UpdateRouteServerPeople,
};

int CWorldRoute::TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge *pUserBridge)
{
	CUserBridgeNet  *pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic  *pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	//
	//select检测是否有空间
	fd_set SetWrite;
	int nResult=0;
	timeval TimeSelect;

	TimeSelect.tv_sec=1;
	TimeSelect.tv_usec=0;

	FD_ZERO(&SetWrite);
	FD_SET(pUserBridgeNet->nSocket, &SetWrite);

	nResult = select(0, NULL, &SetWrite, NULL, &TimeSelect);
	if( nResult>0 )
	{
		nResult = CCommonSocket::SendnTCP(pUserBridgeNet->nSocket, (char*)pSendMsgBase, pSendMsgBase->nSizeOfMsg);
		if( nResult<0 )
		{			
			return -1;
		}
	}
	else if( SOCKET_ERROR==nResult )
	{
		return -1;		
	}

	return 0;
}

void CWorldRoute::Close(CUserBridge* pUserBridge)
{

}

void CWorldRoute::CallBackClose(int nNetKey)
{

}

int CWorldRoute::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge *pUserBridge )
{		
	int nResult;

	nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);

	if( -1==nResult )
	{
		Close(pUserBridge);
	}
	
	return nResult;
}


int CWorldRoute::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgSayHello *pMsgSayHello = (MsgSayHello *)pMsgBase;

	printf("Warning, HelloWorld:%s\n", pMsgSayHello->Buffer);

	return 0;
}

int CWorldRoute::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("It's no my Protocol!, Protocol OrderAction is:%d", pMsgBase->__nActionOrder);
	return -1;	
}


int CWorldRoute::UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge)
{
	CUserBridgeNet  *pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic  *pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgServerUpdatePeople *pMsgServerUpdatePeople = (MsgServerUpdatePeople*)pMsgBase;

	pMsgServerUpdatePeople->nPeople = g_WorldBinPlay.MRoleManager.GetMRoleSumUse();
	
	if( -1==TCPSend(pMsgBase, pUserBridge) )
	{
		printf("CWorldRoute::UpdateRouteServerPeople:%d\n", WSAGetLastError());		
		return -1;
	}

	return 0;
}