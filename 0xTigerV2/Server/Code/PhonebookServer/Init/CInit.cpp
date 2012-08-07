#include "StdAfx.h"
#include "CInit.h"

initialiseSingleton(CInit);

CInit::CInit()
{
	/*
		ע������������˳����ͷ����෴
	*/
	InitCommonLib();
	InitLog();
	InitPackets();
	InitRoleAllocator();
}

CInit::~CInit()
{
	DeleteRoleAllocator();
	DeletePackets();
	DeleteLog();
	DeleteCommonLib();
}

void CInit::InitCommonLib()
{
	new CCommonLibInit;
}
void CInit::DeleteCommonLib()
{
	delete CCommonLibInit::getSingletonPtr();
}

void CInit::InitLog()
{
	
}
void CInit::DeleteLog()
{

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