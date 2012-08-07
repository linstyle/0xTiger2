//PhonebookServer,mainº¯Êý¹ÜÀí
#include "StdAfx.h"
#include "CMaster.h"
#include "Init/CInit.h"

initialiseSingleton(CMaster);

extern volatile bool g_bQuit;

CMaster::CMaster()
{
	ServerInit();
}
CMaster::~CMaster()
{
	ServerExit();
}

void CMaster::ServerInit()
{
	new CInit;

	g_NetDriver.Init(NULL, 0, &NetAccept, 1);
}

bool CMaster::ServerLoop()
{
	LOG(LOG_ERROR,  L"lindp, LOG_ERROR\n");
	LOG(LOG_NOTIC,  L"lindp, LOG_NOTIC\n");
	LOG(LOG_WARN,  L"lindp, LOG_WARN\n");
	//g_NetDriver.Run();
	//g_NetDriver.TracerMe();
	return true;
}

void CMaster::ServerExit()
{
	g_ThreadPool.Exit();

	delete CInit::getSingletonPtr(); 
}