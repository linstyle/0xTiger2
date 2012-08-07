#include "StdAfx.h"
#include "CConfigRead.h"

CConfigRead g_ConfigRead;

void CConfigRead::Read_CNetConnect(USHORT *pPort, ULONG *pIP)
{
	char BuffIP[24];

	*pPort = GetPrivateProfileIntA("SOCKET", "CONNECT_PORT", 1, "Config\\WeightServer.ini");
	GetPrivateProfileStringA("SOCKET", "CONNECT_IP", "255.255.255.255", BuffIP, 16, "Config\\WeightServer.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L = inet_addr("255.255.255.255");

	MTVERIFY( 1!=*pPort );
	MTVERIFY( 1!=*pIP );
	
}