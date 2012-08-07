#pragma once
#include "../stdafx.h"
#include "../Bridge/CUserBridge.h"


#include "Protocol/Protocol_Server_BinPlay.h"
#include "Network/CNetworkPublic.h"
#include "../Standalone/Scene/CSceneManager.h"
/*
��Ϊ��binҲ�������û�������bin��play����Ϣ������ߵ��߼��ࡣ
*/

class CWorldServer
{
public:
	CSceneManager SceneManager;

private:

public:
	CWorldServer();
	~CWorldServer();
	
	int TCPSend(CUserBridge* pUserBridge, MsgBaseHead *pSendMsgBase);

	/*
		������ת��ĺ���ָ��
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldServer::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	/*
		����ת����
	*/
	void Close(CMRole *pMRole);
	void FillPackBuffer(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge, int nMsgBaseOffset);


private:
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test1(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

};