#include "CConfigManager.h"

CConfigManager ConfigManager;
/*
	ȫ�ֵ�һЩ��������
*/
namespace name_global
{
	int nLineIdenti		= -1;			//�ڼ���
	int nGlobalIdenti	= -1;			//��BIN��������Ψһ�ı�ʶ
	int nMaxPostofficeCount = -1;		//��Ҫ���ӵ�������
	int nMaxMRoleCount  = -1;			//�ó������֧����������
};

CConfigManager::CConfigManager()
{
	ReadLineIdenti();
	ReadGlobalIdenti();	
	ReadMaxPostofficeCount();
	ReadMaxMRoleCount();
}

int CConfigManager::GetLineIdenti()
{
	return name_global::nLineIdenti;
}

int CConfigManager::GetGlobalIdenti()
{
	return name_global::nGlobalIdenti;
}

int CConfigManager::GetMaxPostofficeCount()
{
	return name_global::nMaxPostofficeCount;
}

int CConfigManager::GetMaxMRoleCount()
{
	if( -1==name_global::nMaxMRoleCount )
	{
		ReadMaxMRoleCount();		
	}
	return name_global::nMaxMRoleCount ;
}


void CConfigManager::ReadLineIdenti()
{
	name_global::nLineIdenti = GetPrivateProfileIntA("MY_INFO", "LINE_IDENTI", -1, "Config\\ServerBin\\ServerBin.ini");
	MTVERIFY( -1!=name_global::nLineIdenti );
}

void CConfigManager::ReadGlobalIdenti()
{
	name_global::nGlobalIdenti = GetPrivateProfileIntA("MY_INFO", "BIN_IDENTI", -1, "Config\\ServerBin\\ServerBin.ini");
	MTVERIFY( -1!=name_global::nGlobalIdenti );
}

void CConfigManager::ReadMaxPostofficeCount()
{
	name_global::nMaxPostofficeCount = GetPrivateProfileIntA("ROUTE_TCP_SOCKET", "CONNECT_POSTOFFICE_COUNT", -1, "Config\\ServerBin\\ServerBin.ini");
	MTVERIFY( -1!=name_global::nMaxPostofficeCount );
}

void CConfigManager::ReadMaxMRoleCount()
{
	name_global::nMaxMRoleCount = GetPrivateProfileIntA("MY_INFO", "MAX_MROLE_COUNT", -1, "Config\\ServerBin\\ServerBin.ini");
	MTVERIFY( -1!=name_global::nMaxMRoleCount );
}
/*
	����ģ��
*/
void CConfigManager::ReadConnectPostofficeServer(int nIndex, int *pPort, unsigned long *pIP)
{
	char KeyIP[64], KeyPort[64];
	char BuffIP[16];

	sprintf(KeyIP, "CONNECT_POSTOFFICE_SERVER_IP_%d", nIndex);
	sprintf(KeyPort, "CONNECT_POSTOFFICE_SERVER_PORT_%d", nIndex);

	
	GetPrivateProfileStringA("ROUTE_TCP_SOCKET", KeyIP, "255.255.255.255", BuffIP, 16, "Config\\ServerBin\\ServerBin.ini");
	*pPort = GetPrivateProfileIntA("ROUTE_TCP_SOCKET", KeyPort, -1, "Config\\ServerBin\\ServerBin.ini");

	*pIP = inet_addr(BuffIP);
	unsigned long L =inet_addr("255.255.255.255");

	MTVERIFY( -1!=*pPort );
	MTVERIFY( L!=*pIP );
}


void CConfigManager::ReadSceneCount(int *pSceneMaxCount)
{
	*pSceneMaxCount = GetPrivateProfileIntA("SCENE", "SCENE_COUNT", -1, "Config\\ServerBin\\ServerBin.ini");

	MTVERIFY( -1!=*pSceneMaxCount );	
}

void CConfigManager::ReadSceneSelfInfo(int nIndex, int *pSceneIdenti)
{
	char BufferIdenti[32];
	
	sprintf(BufferIdenti, "SCENE_IDENTI_OF_%d", nIndex);

	*pSceneIdenti = GetPrivateProfileIntA("SCENE", BufferIdenti, -1, "Config\\ServerBin\\ServerBin.ini");

	MTVERIFY( -1!=*pSceneIdenti );
}