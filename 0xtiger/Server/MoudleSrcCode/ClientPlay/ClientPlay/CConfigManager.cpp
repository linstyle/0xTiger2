#include "CConfigManager.h"

void CConfigManager::ReadClientLoginConnect(int *pPorts, unsigned long *pIP)
{
	char BuffIP[16];

	*pPorts = ReadClientLoginConnectPort();
	GetPrivateProfileStringA("UDP_SOCKET", "CONNECT_IP", "255.255.255.255", BuffIP, 16, "Config\\ClientPlay\\ClientPlay.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPorts );
	MTVERIFY( L!=*pIP );

}

int CConfigManager::ReadClientLoginConnectPort()
{
	int Port, nPortNumberOf, nPortIndex;

	nPortNumberOf = GetPrivateProfileIntA("UDP_SOCKET", "CONNECT_PORT_NUMBER", -1, "Config\\ClientPlay\\ClientPlay.ini");
	MTVERIFY( -1!=nPortNumberOf );

	char strPortValueName[16];
	srand(GetTickCount());

	nPortIndex = rand()%nPortNumberOf;
	sprintf(strPortValueName, "CONNECT_PORT_%d", nPortIndex);

	Port = GetPrivateProfileIntA("UDP_SOCKET", strPortValueName, -1, "Config\\ClientPlay\\ClientPlay.ini");
	MTVERIFY( -1!=Port );

	return Port;
}