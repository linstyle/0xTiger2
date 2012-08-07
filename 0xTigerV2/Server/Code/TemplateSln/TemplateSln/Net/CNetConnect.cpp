#include "StdAfx.h"
#include "CNetConnect.h"
#include "../CConfigRead.h"


CNetConnect::CNetConnect():ILocalObjectConnect("CNetConnect")
{
	ReadConfig();	
}

void CNetConnect::ReadConfig()
{
	g_ConfigRead.Read_CNetConnect(&m_nPort, &m_nIP);
}


