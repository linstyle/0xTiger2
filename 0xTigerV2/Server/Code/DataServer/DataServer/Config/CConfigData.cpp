#include "stdafx.h"
#include "CConfigData.h"

DATA_SERVER_NET::DATA_SERVER_NET()
{	
	nAcceptPort = -1;

}

DATA_SERVER_NET::~DATA_SERVER_NET()
{
	delete []pGateWayIP	;
	delete []pGateWayPort;
}

DATA_SERVER_GUID::DATA_SERVER_GUID()
{
	GUID_HUMAN_BEGIN = 0;
	GUID_HUMAN_END = 0 ;

	GUID_ITEM_BEGIN = 0;
	GUID_ITEM_END = 0;

	GUID_MONSTER_BEGIN = 0;
	GUID_MONSTER_END = 0;	
}