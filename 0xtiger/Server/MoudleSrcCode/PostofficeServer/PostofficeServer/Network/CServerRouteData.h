#pragma once

#include "../CConfigManager.h"

//�����ṩ����ҵ�����IP��ַ
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