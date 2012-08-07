#include "StdAfx.h"
#include "CConfigRead.h"

initialiseSingleton(CConfigRead);

CConfigRead::CConfigRead()
{
	Init();
}

void CConfigRead::Init()
{
	//依次读入所有的配置文件
	ReadGateWayServer();
    ReadGateWayGUID();
}

//关于服务器本身的配置
void CConfigRead::ReadGateWayServer()
{
	m_GateWayNet.nAcceptPort = GetPrivateProfileInt(L"SOCKET", L"LOCAL_PORT", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayNet.nAcceptPort );

	m_GateWayNet.nMaxConnectClient = GetPrivateProfileInt(L"SOCKET", L"MAX_CONNECT_CLIENT", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayNet.nMaxConnectClient );

	m_GateWayNet.nMaxConnectChatServer = GetPrivateProfileInt(L"SOCKET", L"MAX_CONNECT_CHAT_SERVER", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayNet.nMaxConnectChatServer );

	m_GateWayNet.nMaxConnectDataServer = GetPrivateProfileInt(L"SOCKET", L"MAX_CONNECT_DATA_SERVER", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayNet.nMaxConnectDataServer );
}

void CConfigRead::ReadGateWayGUID()
{
	//HUMAN
	m_GateWayGUID.GUID_HUMAN_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_HUMAN_BEGIN", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_HUMAN_BEGIN );

	m_GateWayGUID.GUID_HUMAN_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_HUMAN_END", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_HUMAN_END );		

	//ITEM
	m_GateWayGUID.GUID_ITEM_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_ITEM_BEGIN", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_ITEM_BEGIN);		

	m_GateWayGUID.GUID_ITEM_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_ITEM_END", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_ITEM_END );

	//MONSTER
	m_GateWayGUID.GUID_MONSTER_BEGIN = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_MONSTER_BEGIN", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_MONSTER_BEGIN );

	m_GateWayGUID.GUID_MONSTER_END = GetPrivateProfileInt(L"GUID", L"GAME_IDENTI_MONSTER_END", 0, L"Config\\GatewayServer.ini");
	MTVERIFY( 0!=m_GateWayGUID.GUID_MONSTER_END);	
}

GATEWAY_NET* CConfigRead::GetGateWayNet()
{
	return &m_GateWayNet;
}
GATEWAY_GUID* CConfigRead::GetGeteWayGUID()
{
	return &m_GateWayGUID;
}