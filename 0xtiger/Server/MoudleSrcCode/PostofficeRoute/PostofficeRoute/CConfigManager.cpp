#include "CConfigManager.h"

int CConfigManager::nMaxConnectItem = -1;

//
//±¾Ä£¿é
void CConfigManager::ReadMaxConnectItem()
{
	nMaxConnectItem = GetPrivateProfileIntA("TCP_SOCKET", "MAX_CONNECT_ITEM", -1, "Config\\PostofficeRoute\\PostofficeRoute.ini");
	
	MTVERIFY( -1!=nMaxConnectItem  );
}

void CConfigManager::ReadRouteMain(int *pCPUNumberOf)
{
	*pCPUNumberOf = GetPrivateProfileIntA("SYS_INFO", "CPU_NUMBER_OF", -1, "Config\\PostofficeRoute\\PostofficeRoute.ini");

	MTVERIFY( -1!=*pCPUNumberOf );
}

void CConfigManager::ReadRouteUDPListen(int nIndex, int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];
	char PortValueName[64];
	char IPValueName[64];

	sprintf(PortValueName, "%s_%d", "LISTEN_LOCAL_PORT", nIndex);
	sprintf(IPValueName, "%s_%d", "LISTEN_LOCAL_IP", nIndex);

	*pPorts = GetPrivateProfileIntA("UDP_SOCKET", PortValueName, -1, "Config\\PostofficeRoute\\PostofficeRoute.ini");
	GetPrivateProfileStringA("UDP_SOCKET", IPValueName, "255.255.255.255", BuffIP, 16, "Config\\PostofficeRoute\\PostofficeRoute.ini");
	
	*pIP = inet_addr(BuffIP);
	unsigned long L = inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );
}

void CConfigManager::ReadRouteRand(int *pMaxServerPeople)
{
	*pMaxServerPeople = GetPrivateProfileIntA("POSTOFFICE_SERVER", "MAX_SERVER_PEOPLE", 0, "Config\\PostofficeRoute\\PostofficeRoute.ini");

	MTVERIFY( 0!=*pMaxServerPeople );
}

void CConfigManager::ReadRouteTCPListen(int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];

	*pPorts = GetPrivateProfileIntA("TCP_SOCKET", "LISTEN_LOCAL_PORT", -1, "Config\\PostofficeRoute\\PostofficeRoute.ini");
	GetPrivateProfileStringA("TCP_SOCKET", "LISTEN_LOCAL_IP", "255.255.255.255", BuffIP, 16, "Config\\PostofficeRoute\\PostofficeRoute.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );

}