#include "StdAfx.h"
#include "CInitPackets.h"


initialiseSingleton(CInitPackets);

CInitPackets::CInitPackets()
{
	InitPackets();
}
	
CInitPackets::~CInitPackets()
{
	DeletePackets();
}

void CInitPackets::InitPackets()
{
	new PExceptionObject;
	new PAcceptObject;
	new PFileTransObject;
}

void CInitPackets:: DeletePackets()
{
	delete PFileTransObject::getSingletonPtr();
	delete PAcceptObject::getSingletonPtr();
	delete PExceptionObject::getSingletonPtr();
}