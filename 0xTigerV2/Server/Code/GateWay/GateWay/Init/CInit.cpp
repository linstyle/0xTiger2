#include "StdAfx.h"
#include "CInit.h"
#include "GameEnum.h"
initialiseSingleton(CInit);

CInit::CInit()
{
	/*
		注意这里申明的顺序和释放中相反
	*/
	InitConfigRead();
	InitCommonLib();
	InitLog();
	InitRoleConnectManager();
	InitGUID();
	InitPackets();
	InitRoleAllocator();
}

CInit::~CInit()
{
	DeleteRoleAllocator();
	DeletePackets();
	DeleteGUID();
	DelRoleConnectManager();
	DeleteLog();
	DeleteCommonLib();
	DeleteConfigRead();
}


void CInit::InitCommonLib()
{
	new CCommonLibInit;
}
void CInit::DeleteCommonLib()
{
	delete CCommonLibInit::getSingletonPtr();
}

void CInit::InitConfigRead()
{
	new CConfigRead;
}
void CInit::DeleteConfigRead()
{
	delete CConfigRead::getSingletonPtr();
}

VOID CInit::InitGUID()
{
	new CMGuid;

	GATEWAY_GUID *pGateWayGuid = g_ConfigRead.GetGeteWayGUID();

	GUID_SET GuidSet[GAME_IDENTI_COUNT_MAX];
	for(int i=0; i<GAME_IDENTI_COUNT_MAX; ++i)
	{
		GuidSet[i].m_nGuidBegin = SpliteConfigGuid(pGateWayGuid, (GAME_IDENTI_TYPE)i);
		GuidSet[i].m_nGuidEnd = GuidSet[i].m_nGuidBegin;
	}
	g_Guid.Init(500, L"Config\\GatewayServer.ini", GuidSet);
}

unsigned int CInit::SpliteConfigGuid(GATEWAY_GUID *pGateWayGuid, GAME_IDENTI_TYPE IdentiType)
{
	switch(IdentiType)
	{
	case GAME_IDENTI_HUMAN:
		return pGateWayGuid->GUID_HUMAN_BEGIN;	
		break;
	case GAME_IDENTI_ITEM:
		return pGateWayGuid->GUID_ITEM_BEGIN;
		break;
	case GAME_IDENTI_MONSTER:
		return pGateWayGuid->GUID_MONSTER_BEGIN;
		break;
	default:
		MTVERIFY(0);
	}
	
	return 0;
}
void CInit::DeleteGUID()
{
	delete CMGuid::getSingletonPtr();
}

void CInit::InitLog()
{
	
}
void CInit::DeleteLog()
{

}

void CInit::InitRoleConnectManager()
{
	new CRoleConnectManager;
}

void CInit::DelRoleConnectManager()
{
	delete CRoleConnectManager::getSingletonPtr();
}

void CInit::InitPackets()
{
	new CInitPackets;
}
void CInit::DeletePackets()
{
	delete CInitPackets::getSingletonPtr();
}


void CInit::InitRoleAllocator()
{	
	new CRoleAllocator;
}
void CInit::DeleteRoleAllocator()
{
	delete CRoleAllocator::getSingletonPtr();
}