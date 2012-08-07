#include "StdAfx.h"
#include "CConfigRead.h"
#include "GlobalFunction.h"

initialiseSingleton(CConfigRead);

CConfigRead::CConfigRead()
{
	Init();
}

void CConfigRead::Init()
{
	//依次读入所有的配置文件
	ReadDataServer();
    ReadDataServerGUID();
}

//关于服务器本身的配置
void CConfigRead::ReadDataServer()
{
	/*
		读取网络数据
	*/
	m_DataServerNet.nGateWayCount = GetPrivateProfileInt(L"SOCKET", L"GATEWAY_COUNT", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerNet.nGateWayCount );
	m_DataServerNet.pGateWayIP = new unsigned long[m_DataServerNet.nGateWayCount];
	m_DataServerNet.pGateWayPort= new int[m_DataServerNet.nGateWayCount];

	int i;
	wchar_t KeyTempBuffer[64], ValueTempIP[48];
	for(i=0; i<m_DataServerNet.nGateWayCount; i++)
	{
		memset(KeyTempBuffer, 0, sizeof(KeyTempBuffer) );
		memset(ValueTempIP, 0 ,sizeof(ValueTempIP) );
		wsprintf(KeyTempBuffer, L"CONNECT_GATEWAY_IP_%d", i);
		GetPrivateProfileString(L"SOCKET", KeyTempBuffer, L"255.255.255.255", ValueTempIP, 16, L"Config\\DataServer.ini");
		
		m_DataServerNet.pGateWayIP[i] = inet_addr_w(ValueTempIP);
		unsigned long L = inet_addr("255.255.255.255");

		MTVERIFY( L!=m_DataServerNet.pGateWayIP[i] );
	}

	for(i=0; i<m_DataServerNet.nGateWayCount; i++)
	{
		memset(KeyTempBuffer, 0, sizeof(KeyTempBuffer) );
		wsprintf(KeyTempBuffer, L"CONNECT_GATEWAY_PORT_%d", i);

		m_DataServerNet.pGateWayPort[i] = GetPrivateProfileInt(L"SOCKET", KeyTempBuffer, 0, L"Config\\DataServer.ini");
		MTVERIFY( 0!=m_DataServerNet.pGateWayPort[i] );
	}

	m_DataServerNet.nAcceptPort = GetPrivateProfileInt(L"SOCKET", L"LOCAL_PORT", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerNet.nAcceptPort );
}

void CConfigRead::ReadDataServerGUID()
{
	//HUMAN
	m_DataServerGUID.GUID_HUMAN_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_HUMAN_BEGIN", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_HUMAN_BEGIN );

	m_DataServerGUID.GUID_HUMAN_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_HUMAN_END", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_HUMAN_END );		

	//ITEM
	m_DataServerGUID.GUID_ITEM_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_ITEM_BEGIN", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_ITEM_BEGIN);		

	m_DataServerGUID.GUID_ITEM_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_ITEM_END", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_ITEM_END );

	//MONSTER
	m_DataServerGUID.GUID_MONSTER_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_MONSTER_BEGIN", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_MONSTER_BEGIN );

	m_DataServerGUID.GUID_MONSTER_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_MONSTER_END", 0, L"Config\\DataServer.ini");
	MTVERIFY( 0!=m_DataServerGUID.GUID_MONSTER_END);	
}

DATA_SERVER_NET* CConfigRead::GetDataServerNet()
{
	return &m_DataServerNet;
}
DATA_SERVER_GUID* CConfigRead::GetDataServerGUID()
{
	return &m_DataServerGUID;
}