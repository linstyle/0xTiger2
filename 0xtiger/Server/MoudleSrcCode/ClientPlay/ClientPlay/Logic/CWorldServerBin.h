#pragma once

#include "../stdafx.h"
#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Server_BinPlay.h"

class CWorldServerBin
{
public:

private:

public:
	//
	//控制发送
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);

	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldServerBin::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	/*
		非跳转函数
	*/
	void Close(CUserBridge* pUserBridge);

private:
	/*
		定义跳转表的函数指针
	*/
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

};