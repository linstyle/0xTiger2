#include "stdafx.h"
#include "CConfigData.h"

GATEWAY_NET::GATEWAY_NET()
{
	nAcceptPort = -1;
	nMaxConnectChatServer = 0;
	nMaxConnectClient = 0;
	nMaxConnectDataServer = 0;
}

GATEWAY_GUID::GATEWAY_GUID()
{
	GUID_HUMAN_BEGIN = 0;
	GUID_HUMAN_END = 0 ;

	GUID_ITEM_BEGIN = 0;
	GUID_ITEM_END = 0;

	GUID_MONSTER_BEGIN = 0;
	GUID_MONSTER_END = 0;	
}