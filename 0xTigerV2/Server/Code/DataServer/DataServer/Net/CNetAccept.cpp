#include "StdAfx.h"
#include "CNetAccept.h"
#include "../Config/CConfigRead.h"

void CNetAccept::Init()
{
	ReadConfig();
}

void CNetAccept::ReadConfig()
{
	DATA_SERVER_NET *pDataServerNet = g_ConfigRead.GetDataServerNet();
	ILocalObjectAccept::Init("CNetAccept", 0, pDataServerNet->nAcceptPort);
}
