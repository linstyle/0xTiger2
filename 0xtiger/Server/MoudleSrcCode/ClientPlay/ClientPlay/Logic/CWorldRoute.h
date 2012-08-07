#pragma once

#include "../stdafx.h"
#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Route_Play.h"

class CWorldRoute
{
public:

private:

public:
	/*
		该处都为消息解析函数跳转
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldRoute::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

private:
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int AskEncryption(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

};