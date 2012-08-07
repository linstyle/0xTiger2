#include "CWorldServerBin.h"
#include "../stdafx.h"

CWorldServerBin g_WorldServerBin;



CWorldServerBin::RESOLVE_MSG CWorldServerBin::ResoleveFn[] = 
{
	&CWorldServerBin::HelloWorld,
	&CWorldServerBin::__FillFunc,
	&CWorldServerBin::Test
};

int CWorldServerBin::TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge)
{/*
	WSABUF WSASocketSendBuff;
	DWORD nSendBytes=0, nSendFlags=0;
	int nResult, nSenderAddrSize = sizeof(pUserBridgeNet->SenderAddr);
	
	WSASocketSendBuff.buf = (char*)pSendMsgBase;
	WSASocketSendBuff.len = pSendMsgBase->nSizeOfMsg;


	nResult = WSASendTo(pUserBridgeNet->nSocketSend, &WSASocketSendBuff, 1, &nSendBytes, nSendFlags, 
					    (SOCKADDR *) &pUserBridgeNet->SenderAddr, nSenderAddrSize, NULL, NULL);
	if(SOCKET_ERROR == nResult)
	{
		cout<<"CWorldServerBin::SocketUDPSend:"<<WSAGetLastError()<<endl;
		//
		//close socket or other doing.
		return -1;
	}
*/
	return 0;
}

int CWorldServerBin::ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult = (this->*(ResoleveFn[pMsgBase->__nActionOrder]))(pMsgBase, pUserBridge);

	if( -1==nResult )
	{
		Close(pUserBridge);
	}
	
	return nResult;
}

int CWorldServerBin::__FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	printf("It's no my Protocol!, Protocol OrderAction is:%d", pMsgBase->__nActionOrder);		
	return -1;
}

void CWorldServerBin::Close(CUserBridge* pUserBridge)
{

}


int CWorldServerBin::HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgSayHello *pMsgSayHello = (MsgSayHello *)pMsgBase;

	printf("Warning, HelloWorld:%s\n", pMsgSayHello->Buffer);

	/*
		处理后返回,如果是客户端不做处理
	
	char *p = pMsgSayHello->Buffer+strlen(pMsgSayHello->Buffer);
	strcpy(p, "Yeah! I have receive your 'say hello'");

	nResult = TCPSend(pMsgBase, pUserBridge);
	if( -1==nResult )
	{
		printf("Err, CWorldServerBin::HelloWorld:%d \n", WSAGetLastError());
	}
	*/

	return 0;
}


int CWorldServerBin::Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	int nResult;
	switch( pMsgBase->__nActionDo )
	{
	case 0:
		break;

	case 2:
		nResult = Test2(pMsgBase, pUserBridge);
		break;

	default:
		nResult = __FillFunc(pMsgBase, pUserBridge);
	}

	return nResult;
}

int CWorldServerBin::Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge)
{
	CUserBridgeNet* pUserBridgeNet = &pUserBridge->UserBridgeNet;
	CUserBridgeLogic* pUserBridgeLogic = &pUserBridge->UserBridgeLogic;

	MsgTest3 *pMsgTest3 = (MsgTest3*)pMsgBase;

	printf("Warning, CWorldServerBin::Test2, money:%d\n", pMsgTest3->nMoney);

	return 0;
}

