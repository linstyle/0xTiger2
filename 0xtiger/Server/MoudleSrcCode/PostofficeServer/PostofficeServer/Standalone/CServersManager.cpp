#include "CServersManager.h"


//
//
//public
CServersManager::CServersManager()
{
	for(int i=0; i<name_servers_manager::SERVER_DPC_NUMBER_OF+name_servers_manager::SERVER_BIN_NUMBER_OF; i++)
	{
		ServerInfo[i].nIdentification = i;
	}
}

//
//¶ÔbinµÄ²Ù×÷
SERVER_INFO* CServersManager::GetServerInfo(int nIndex)
{
	return &ServerInfo[nIndex];
}

bool CServersManager::IsExisted(const int nBinIdenti)
{
	if( true==ServerInfo[nBinIdenti].bEnable )
	{
		return true;
	}

	return false;
}

void  CServersManager::DisableServerInfo(int nIndex)
{
	ServerInfo[nIndex].bEnable = false;
}

void CServersManager::EnableServerInfo(int nIndex)
{
	ServerInfo[nIndex].bEnable = true;
}

//
//
//private

