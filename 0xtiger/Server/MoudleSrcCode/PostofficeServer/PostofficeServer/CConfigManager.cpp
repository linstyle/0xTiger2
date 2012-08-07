#include "CConfigManager.h"

CConfigManager ConfigManager;

namespace name_global
{
	int nMaxConnectItem = -1;	//最大允许连接数
	int nGlobalIdenti	= 0;	//在整个服务器组件中，邮局组的唯一标识
};


CConfigManager::CConfigManager()
{
	ReadMaxConnectItem();
	ReadGlobalIdenti();
}


void CConfigManager::ReadMaxConnectItem()
{
	name_global::nMaxConnectItem = GetPrivateProfileIntA("IOCP_SOCKET", "MAX_CONNECT_ITEM", -1, "Config\\PostofficeServer\\PostofficeServer.ini");

	MTVERIFY( -1!=name_global::nMaxConnectItem   );
}

void CConfigManager::ReadGlobalIdenti()
{
	name_global::nGlobalIdenti = GetPrivateProfileIntA("MY_INFO", "SERVER_IDENTI", -1, "Config\\PostofficeServer\\PostofficeServer.ini");

	MTVERIFY( -1!=name_global::nGlobalIdenti );
}

int CConfigManager::GetMaxConnectItem()
{
	return name_global::nMaxConnectItem;
}

int CConfigManager::GetGlobalIdenti()
{
	return name_global::nGlobalIdenti;
}


/*
	全局模块
*/
void CConfigManager::ReadConnectPostofficeRoute(int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];

	*pPorts = GetPrivateProfileIntA("ROUTE_TCP_SOCKET", "CONNECT_POSTOFFICE_ROUTE_PORT", -1, "Config\\PostofficeServer\\PostofficeServer.ini");
	GetPrivateProfileStringA("ROUTE_TCP_SOCKET", "CONNECT_POSTOFFICE_ROUTE_IP", "255.255.255.255", BuffIP, 16, "Config\\PostofficeServer\\PostofficeServer.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );	
}

void CConfigManager::ReadPlayIOCPLocal(int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];

	*pPorts = GetPrivateProfileIntA("IOCP_SOCKET", "LISTEN_CLIENT_PORT", -1, "Config\\PostofficeServer\\PostofficeServer.ini");
	GetPrivateProfileStringA("IOCP_SOCKET", "LISTEN_CLIENT_IP", "255.255.255.255", BuffIP, 16, "Config\\PostofficeServer\\PostofficeServer.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );		

}


void CConfigManager::ReadServerSelfInfo( int *pServerIdenti )
{
	*pServerIdenti = GetPrivateProfileIntA("MY_INFO", "SERVER_IDENTI", -1, "Config\\PostofficeServer\\PostofficeServer.ini");

	MTVERIFY( -1!=*pServerIdenti );	
}

void CConfigManager::ReadGameInfo(int *pLineNumberOf, int *pMaxBinCount)
{
	*pLineNumberOf = GetPrivateProfileIntA("GAME_INFO", "LINE_NUMBER_OF", -1, "Config\\PostofficeServer\\PostofficeServer.ini");
	*pMaxBinCount = GetPrivateProfileIntA("GAME_INFO", "MAX_BIN_COUNT", -1, "Config\\PostofficeServer\\PostofficeServer.ini");


	MTVERIFY( -1!=*pLineNumberOf );	
	MTVERIFY( -1!=*pMaxBinCount );	
}