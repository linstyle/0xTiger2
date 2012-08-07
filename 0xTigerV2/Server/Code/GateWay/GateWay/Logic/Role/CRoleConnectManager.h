/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/03/03                                                        
    ����˵����  ���ӵĹ���
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
		���ؿͻ��˵Ķ���
		Guid:�ͻ��˵�G��־�������ݷ������ṩ
	*/
	void AddConnectClient(CRole* pRoleClient, MGUID Guid);	
	void DelConnectClient(MGUID Guid);
	CRole* GetConnectClient(MGUID Guid);

	/*
		��������������Ķ���
		nIndex:����������ı�־����������������������ļ�������(0,1,2,3,4....)
	*/
	void AddConnectChatServer(CRole* pRoleChat, int nIndex);
	CRole* GetConnectChatServer(int nIndex);

	/*
		����DataServer�Ķ���
		nIndex:����������ı�־����������������������ļ�������(0,1,2,3,4....)
	*/
	void AddConnectDataServer(CRole* pRoleChat, int nIndex);
	CRole* GetConnectDataServer(int nIndex);

private:
	void Init();

public:

private:
	//��̨���������
	CRole **m_pMapConnectChatServer;
	int m_nMaxConnectChatServer;

	//��̨Data������
	CRole **m_pMapConnectDataServer;
	int m_nMaxConnectDataServer;

	//�û��ͻ���
	map<MGUID, CRole*> m_MapConnectClient;
	int m_nMaxConnectClient;
};

#define g_RoleConnectManager CRoleConnectManager::getSingleton()