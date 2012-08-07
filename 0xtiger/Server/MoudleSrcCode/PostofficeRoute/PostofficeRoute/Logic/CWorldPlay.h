#pragma once

#include "../Bridge/CUserBridge.h"
#include "Protocol/Protocol_Route_Play.h"
#include "../Standalone/CRouteRand.h"
extern CRouteRand g_RouteRand;

//
//ʵ��Э���߼������ݣ�Ϊ�˱���ͳһ������World.
//���ҽ��׽��ַ��͵ĵ�Ȩ�޽�������
class CWorldPlay
{
public:

private:
	

public:
	/*
		�ô�Ϊ��Ϣ����������ת
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
