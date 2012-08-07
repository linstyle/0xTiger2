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
		�ô���Ϊ��Ϣ����������ת
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldRoute::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

private:
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int AskEncryption(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

};