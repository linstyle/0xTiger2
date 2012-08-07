#pragma once

#include "../Bridge/CUserBridge.h"
#include "../Standalone/CRouteRand.h"
#include "../Standalone/Role/CMRoleManager.h"

#include "Protocol/Protocol_Route_Server.h"
extern CRouteRand g_RouteRand;

/*
	�����߼��࣬��������ṩ��ת�����ӿڣ��رսӿ�,�߼���������ӿ�(��CallBack��ʾ)���Լ�һ����׼�ķ���ֵ��
	���ִ�д����߼���������Ӧ�Ĵ���(��Դ�ͷŵ�)��
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
		�ô�Ϊ��Ϣ����������ת
	*/
	int HelloWorld(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int ServerLogin(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);
	int UpdateRouteServerPeople(MsgBaseHead *pMsgBase, CUserBridge* pUserBridge);

	/*
		TCPSend
		������ͳ�������������ϲ�ر�
	*/
	int TCPSend(MsgBaseHead *pSendMsgBase, CUserBridge* pUserBridge);
	void Close(CUserBridge* pUserBridge);

public:
	/*
		CallBackClose
		����ͨ��NetKey�ؼ���ȡ���߼�����
		Ȼ����ж�����ͷš����
	*/
	void CallBackClose(int nNetKey);
	void CallBackTracerMe();

};