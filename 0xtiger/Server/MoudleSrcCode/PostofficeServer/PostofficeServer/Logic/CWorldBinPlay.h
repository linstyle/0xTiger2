#pragma once
#include "../stdafx.h"
#include "../Bridge/CUserBridge.h"

#include "Network/CServerIOCP.h"
#include "Protocol/Protocol_Server_BinPlay.h"

#include "../Standalone/Role/CMRoleManager.h"
#include "../Standalone/CRouteTableManager.h"
#include "../Standalone/CStandalonePublic.h"
/*
	因为把bin也当成了用户，所以bin和play的消息都走这边的逻辑类。
*/

class CWorldBinPlay
{
public:
	CMRoleManager MRoleManager;
	CRouteTableManager RouteTableManager;

private:

public:
	CWorldBinPlay();
	~CWorldBinPlay();
	
	/*
		TCPPackSend,在尾部植入pack。接时不变。在发送时申明的空间为[协议本身大小+要携带的包]
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);
	int TCPPackSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);

	/*
		定义跳转表的函数指针		
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldBinPlay::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	/*
		非跳转函数
	*/
	int  Close(CUserBridge* pUserBridge);
	int  CallBackClose(CUserBridge* pUserBridge);
	int  CallBackClose(int nIdenti);
	void CallBackTracerMe();

	void FillSendPack(MsgPostHead* pMsgPostHead, CUserBridge* pUserBridge);
	void InitUserBridge(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//int MRoleInfoToLogic(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//debug	
	int Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);	
	int UpdateTest1(CUserBridge* pUserBridge);
	int Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//end debug	

private:
	/*
		执行函数
	*/
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

	int ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int ServerLoginBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int ServerLoginDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );


	/*
		首先取出用户的USER_ROUTE_Navi结构(MRoleHead中)
		其次利用identi从路由表中取到转发的信息
	*/
	int RouteForward( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardClient( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );

};
