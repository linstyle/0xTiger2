#pragma once

#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Route_Server.h"

class CWorldRoute
{
public:

private:

public:
	//
	//定义跳转表的函数指针	
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	typedef int (CWorldRoute::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);

private:
	/*
		TCPSend
		如果发送出错，网络对象由上层关闭
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge *pUserBridge);
	void Close(CUserBridge* pUserBridge);

public:
	/*
		CallBackClose
		首先通过NetKey关键子取到逻辑对象，
		然后进行对象池释放、解绑定
	*/
	void CallBackClose(int nNetKey);
};