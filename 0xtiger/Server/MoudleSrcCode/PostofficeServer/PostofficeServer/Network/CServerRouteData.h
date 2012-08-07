#pragma once

#include "../CConfigManager.h"

//最终提供给玩家的连接IP地址
struct PLAY_CLIENT_INFO
{
	int nPorts;
	unsigned long nIP;
};

class CServerRouteData
{
public:

private:
	PLAY_CLIENT_INFO PlayClientInfo;

public:
	CServerRouteData();

	PLAY_CLIENT_INFO* GetPlayClientInfo()
	{
		return &PlayClientInfo;
	}


private:
	void ReadFromConfigManager();

};