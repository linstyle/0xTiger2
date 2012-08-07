#include "StdAfx.h"
#include "CInit.h"

initialiseSingleton(CInit);



CInit::CInit()
{
	/*
		注意这里申明的顺序和释放中相反
	*/
	InitCommonLib();
	InitPackets();
	InitRoleAllocator();
}

CInit::~CInit()
{
	DeleteRoleAllocator();
	DeletePackets();
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
