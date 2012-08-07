//PhonebookServer,mainº¯Êý¹ÜÀí
#include "StdAfx.h"
#include "CMaster.h"
#include "Init/CInit.h"
#include "CMGuid.h"
initialiseSingleton(CMaster);

extern volatile bool g_bQuit;

CMaster::CMaster()
{
	Init();
}
CMaster::~CMaster()
{
	Exit();
}

void CMaster::Init()
{
	new CInit;
	m_NetMaster.Init();
}

bool CMaster::Loop()
{
	//printf("%I64u\n", g_Guid.MallocGUID(100, GAME_IDENTI_ITEM, 1));
	//printf("%I64u\n", g_Guid.MallocGUID(100, GAME_IDENTI_HUMAN, 1));
	//printf("%I64u\n", g_Guid.MallocGUID(100, GAME_IDENTI_MONSTER, 1));
	//printf("\n");

	//LOG(LOG_ERROR,  L"lindp, LOG_ERROR\n");
	//LOG(LOG_NOTIC,  L"lindp, LOG_NOTIC\n");
	//LOG(LOG_WARN,  L"lindp, LOG_WARN\n");

	//g_NetDriver.Run();
	//g_NetDriver.TracerMe();
	return true;
}

void CMaster::Exit()
{
	g_ThreadPool.Exit();

	delete CInit::getSingletonPtr(); 
}