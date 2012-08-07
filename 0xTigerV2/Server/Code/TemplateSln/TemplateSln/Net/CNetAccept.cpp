#include "StdAfx.h"
#include "CNetAccept.h"
#include "../CConfigRead.h"

CNetAccept::CNetAccept():ILocalObjectAccept("CNetAccept")
{
	ReadConfig();
	//InitSocketTCPS(m_nSocket, m_nIP, m_nPort);
}

void CNetAccept::ReadConfig()
{
	g_ConfigRead.Read_CNetAccept(&m_nPort);
}
