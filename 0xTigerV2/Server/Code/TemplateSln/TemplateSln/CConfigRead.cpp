#include "StdAfx.h"
#include "CConfigRead.h"

CConfigRead g_ConfigRead;

void CConfigRead::Read_CNetAccept(USHORT *pPort)
{
	*pPort = GetPrivateProfileIntA("SOCKET", "LOCAL_PORT", 1, "Config\\TemplateSln.ini");

	MTVERIFY( 1!=*pPort );		
}


void CConfigRead::Read_CNetConnect(USHORT *pPort, ULONG *pIP)
{
	char BuffIP[24];

	*pPort = GetPrivateProfileIntA("SOCKET", "CONNECT_PORT", 1, "Config\\TemplateSln.ini");
	GetPrivateProfileStringA("SOCKET", "CONNECT_IP", "255.255.255.255", BuffIP, 16, "Config\\TemplateSln.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L = inet_addr("255.255.255.255");

	MTVERIFY( 1!=*pPort );
	MTVERIFY( L!=*pIP );
	
}
