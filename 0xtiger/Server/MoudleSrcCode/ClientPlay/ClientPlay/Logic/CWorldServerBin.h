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
	//���Ʒ���
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);

	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldServerBin::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	/*
		����ת����
	*/
	void Close(CUserBridge* pUserBridge);

private:
	/*
		������ת��ĺ���ָ��
	*/
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

};