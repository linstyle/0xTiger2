#include "StdAfx.h"
#include "CRoleConnectManager.h"
#include "../../Config/CConfigRead.h"

initialiseSingleton(CRoleConnectManager);

CRoleConnectManager::CRoleConnectManager()
{
	Init();
}

CRoleConnectManager::~CRoleConnectManager()
{
	delete[] m_pMapConnectChatServer;
	delete[] m_pMapConnectDataServer;
}

void CRoleConnectManager::Init()
{
	GATEWAY_NET *pGateWayNet = g_ConfigRead.GetGateWayNet();
	m_nMaxConnectChatServer = pGateWayNet->nMaxConnectChatServer;
	m_nMaxConnectClient = pGateWayNet->nMaxConnectClient;
	m_nMaxConnectDataServer = pGateWayNet->nMaxConnectDataServer;

	m_pMapConnectChatServer = new CRole*[m_nMaxConnectChatServer];
	memset(m_pMapConnectChatServer, 0, sizeof(CRole*)*m_nMaxConnectChatServer);

	m_pMapConnectDataServer = new CRole*[m_nMaxConnectDataServer];
	memset(m_pMapConnectDataServer, 0, sizeof(CRole*)*m_nMaxConnectDataServer);

}

/*
	Client
*/
void CRoleConnectManager::AddConnectClient(CRole* pRoleClient, MGUID Guid)
{
	m_MapConnectClient.insert(make_pair(Guid, pRoleClient));
}

void CRoleConnectManager::DelConnectClient(MGUID Guid)
{	
	map<MGUID, CRole*>::iterator Iter;

	Iter = m_MapConnectClient.find(Guid);
	if( Iter==m_MapConnectClient.end() )
	{
		printf("Err, CRoleConnectManager::DelServerClient, Find(%I64u)==NULL\n", Guid);
		return;
	}

	m_MapConnectClient.erase(Iter);
}

CRole* CRoleConnectManager::GetConnectClient(MGUID Guid)
{
	return m_MapConnectClient[Guid];

	map<MGUID, CRole*>::iterator Iter;
	Iter = m_MapConnectClient.find(Guid);
	if( Iter==m_MapConnectClient.end() )
	{
		printf("Err, CRoleConnectManager::GetServerClient, Find(%I64u)==NULL\n", Guid);
		return NULL;
	}

	return Iter->second;
}

/*
	ChatServer
*/
void CRoleConnectManager::AddConnectChatServer(CRole* pRoleChat, int nIndex)
{
	assert(nIndex>=m_nMaxConnectChatServer);
	if( nIndex>=m_nMaxConnectChatServer )
	{
		printf("Err, CRoleConnectManager::AddServerCha.nIndex(%d)\n", nIndex);
		return;
	}

	m_pMapConnectChatServer[nIndex] = pRoleChat;
}

CRole* CRoleConnectManager::GetConnectChatServer(int nIndex)
{
	assert(nIndex>=m_nMaxConnectChatServer);
	if( nIndex>=m_nMaxConnectChatServer )
	{
		printf("Err, CRoleConnectManager::GetServerChat.nIndex(%d)\n", nIndex);
		return NULL;
	}

	return m_pMapConnectChatServer[nIndex];
}

/*
	DataServer
*/
void CRoleConnectManager::AddConnectDataServer(CRole* pRoleChat, int nIndex)
{
	assert(nIndex>=m_nMaxConnectDataServer);
	if( nIndex>=m_nMaxConnectDataServer )
	{
		printf("Err, CRoleConnectManager::AddConnectDataServer.nIndex(%d)\n", nIndex);
		return;
	}

	m_pMapConnectDataServer[nIndex] = pRoleChat;
}
CRole* CRoleConnectManager::GetConnectDataServer(int nIndex)
{
	assert(nIndex>=m_nMaxConnectDataServer);
	if( nIndex>=m_nMaxConnectDataServer )
	{
		printf("Err, CRoleConnectManager::GetConnectDataServer.nIndex(%d)\n", nIndex);
		return NULL;
	}

	return m_pMapConnectDataServer[nIndex];
}