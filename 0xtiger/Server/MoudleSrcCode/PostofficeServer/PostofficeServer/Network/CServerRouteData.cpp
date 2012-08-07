#include "CServerRouteData.h"

CServerRouteData ServerRouteData;

CServerRouteData::CServerRouteData()
{
	ReadFromConfigManager();
}

void CServerRouteData::ReadFromConfigManager()
{
	CConfigManager::ReadPlayIOCPLocal(&PlayClientInfo.nPorts, &PlayClientInfo.nIP);
}

