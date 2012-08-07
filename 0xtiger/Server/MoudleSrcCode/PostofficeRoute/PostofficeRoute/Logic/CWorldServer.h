#pragma once

#include "../Bridge/CUserBridge.h"
#include "../Standalone/CRouteRand.h"
#include "../Standalone/Role/CMRoleManager.h"

#include "Protocol/Protocol_Route_Server.h"
extern CRouteRand g_RouteRand;

/*
	世界逻辑类，对网络层提供跳转函数接口，关闭接口,逻辑对象申请接口(以CallBack表示)。以及一个标准的返回值。
	如果执行错误，逻辑类会进行相应的处理(资源释放等)。
*/
class CWorldServer
{
public:
	CMRoleManager MRoleManager; 

private:

public:
	CWorldServer();
	~CWorldServer();

	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldServer::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

private:
	/*
		该处为消息解析函数跳转
	*/
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

	/*
		TCPSend
		如果发送出错，网络对象由上层关闭
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);
	void Close(CUserBridge* pUserBridge);

public:
	/*
		CallBackClose
		首先通过NetKey关键子取到逻辑对象，
		然后进行对象池释放、解绑定
	*/
	void CallBackClose(int nNetKey);
	void CallBackTracerMe();

};