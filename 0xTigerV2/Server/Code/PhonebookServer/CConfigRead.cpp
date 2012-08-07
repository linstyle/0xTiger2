#include "StdAfx.h"
#include "CConfigRead.h"

CConfigRead g_ConfigRead;

void CConfigRead::Read_CNetAccept(USHORT *pPort)
{
	*pPort = GetPrivateProfileIntA("SOCKET", "LOCAL_GAMESERVER_PORT", 1, "Config\\PhonebookServer.ini");

	MTVERIFY( 1!=*pPort );	
}