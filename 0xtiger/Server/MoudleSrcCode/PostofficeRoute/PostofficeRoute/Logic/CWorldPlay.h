#pragma once

#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Route_Play.h"
#include "../Standalone/CRouteRand.h"
extern CRouteRand g_RouteRand;

//
//实现协议逻辑的内容，为了保持统一，都称World.
//并且将套接字发送的的权限交给该类
class CWorldPlay
{
public:

private:
	

public:
	/*
		该处为消息解析函数跳转
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	typedef int (CWorldPlay::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

private:
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int AskEncryption(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);


	int UDPSend(CUserBridgeNet *pUserBridgeNet, MsgBaseHead *pSendMsgBase);
	void Close(CUserBridge* pUserBridge);
};
