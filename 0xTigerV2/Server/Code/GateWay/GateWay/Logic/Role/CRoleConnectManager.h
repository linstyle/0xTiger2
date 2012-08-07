/*  作者：		林东平                                                              
	创建时间：	2011/03/03                                                        
    功能说明：  连接的管理
*/

#pragma once
#include <map>
#include "Singleton.h"
#include "ServerEnum.h"
#include "GlobalType.h"
#include "CRole.h"

using namespace std;


class CRoleConnectManager:public Singleton<CRoleConnectManager>
{
public:
	CRoleConnectManager();
	~CRoleConnectManager();

	/*
		返回客户端的对象
		Guid:客户端的G标志。由数据服务器提供
	*/
	void AddConnectClient(CRole* pRoleClient, MGUID Guid);	
	void DelConnectClient(MGUID Guid);
	CRole* GetConnectClient(MGUID Guid);

	/*
		返回聊天服务器的对象
		nIndex:聊天服务器的标志。各个聊天服务器中配置文件中配置(0,1,2,3,4....)
	*/
	void AddConnectChatServer(CRole* pRoleChat, int nIndex);
	CRole* GetConnectChatServer(int nIndex);

	/*
		返回DataServer的对象
		nIndex:聊天服务器的标志。各个聊天服务器中配置文件中配置(0,1,2,3,4....)
	*/
	void AddConnectDataServer(CRole* pRoleChat, int nIndex);
	CRole* GetConnectDataServer(int nIndex);

private:
	void Init();

public:

private:
	//后台聊天服务器
	CRole **m_pMapConnectChatServer;
	int m_nMaxConnectChatServer;

	//后台Data服务器
	CRole **m_pMapConnectDataServer;
	int m_nMaxConnectDataServer;

	//用户客户端
	map<MGUID, CRole*> m_MapConnectClient;
	int m_nMaxConnectClient;
};

#define g_RoleConnectManager CRoleConnectManager::getSingleton()