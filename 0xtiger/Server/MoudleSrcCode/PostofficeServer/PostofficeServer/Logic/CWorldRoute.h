#pragma once

#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Route_Server.h"

class CWorldRoute
{
public:

private:

public:
	//
	//������ת��ĺ���ָ��	
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	typedef int (CWorldRoute::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge *pUserBridge);

private:
	/*
		TCPSend
		������ͳ�������������ϲ�ر�
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge *pUserBridge);
	void Close(CUserBridge* pUserBridge);

public:
	/*
		CallBackClose
		����ͨ��NetKey�ؼ���ȡ���߼�����
		Ȼ����ж�����ͷš����
	*/
	void CallBackClose(int nNetKey);
};