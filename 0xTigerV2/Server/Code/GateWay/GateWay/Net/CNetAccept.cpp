#include "StdAfx.h"
#include "CNetAccept.h"
#include "../Config/CConfigRead.h"

void CNetAccept::Init()
{
	ReadConfig();
}

void CNetAccept::ReadConfig()
{
	GATEWAY_NET *pGateWayNet = g_ConfigRead.GetGateWayNet();
	ILocalObjectAccept::Init("CNetAccept", 0, pGateWayNet->nAcceptPort);
}
