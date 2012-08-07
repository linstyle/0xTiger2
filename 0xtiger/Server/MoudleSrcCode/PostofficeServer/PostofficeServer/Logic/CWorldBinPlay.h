#pragma once
#include "../stdafx.h"
#include "../Bridge/CUserBridge.h"

#include "Network/CServerIOCP.h"
#include "Protocol/Protocol_Server_BinPlay.h"

#include "../Standalone/Role/CMRoleManager.h"
#include "../Standalone/CRouteTableManager.h"
#include "../Standalone/CStandalonePublic.h"
/*
	��Ϊ��binҲ�������û�������bin��play����Ϣ������ߵ��߼��ࡣ
*/

class CWorldBinPlay
{
public:
	CMRoleManager MRoleManager;
	CRouteTableManager RouteTableManager;

private:

public:
	CWorldBinPlay();
	~CWorldBinPlay();
	
	/*
		TCPPackSend,��β��ֲ��pack����ʱ���䡣�ڷ���ʱ�����Ŀռ�Ϊ[Э�鱾���С+ҪЯ���İ�]
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);
	int TCPPackSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);

	/*
		������ת��ĺ���ָ��		
	*/
	int ResolveMsg( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	typedef int (CWorldBinPlay::*RESOLVE_MSG)(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	static RESOLVE_MSG ResoleveFn[];

	/*
		����ת����
	*/
	int  Close(CUserBridge* pUserBridge);
	int  CallBackClose(CUserBridge* pUserBridge);
	int  CallBackClose(int nIdenti);
	void CallBackTracerMe();

	void FillSendPack(MsgPostHead* pMsgPostHead, CUserBridge* pUserBridge);
	void InitUserBridge(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//int MRoleInfoToLogic(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//debug	
	int Test(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);	
	int UpdateTest1(CUserBridge* pUserBridge);
	int Test2(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	//end debug	

private:
	/*
		ִ�к���
	*/
	int __FillFunc(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

	int ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int ServerLoginBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int ServerLoginDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );


	/*
		����ȡ���û���USER_ROUTE_Navi�ṹ(MRoleHead��)
		�������identi��·�ɱ���ȡ��ת������Ϣ
	*/
	int RouteForward( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardBin( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardDpc( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );
	int RouteForwardClient( MsgBaseHead *pMsgBase, CUserBridge* pUserBridge );

};
