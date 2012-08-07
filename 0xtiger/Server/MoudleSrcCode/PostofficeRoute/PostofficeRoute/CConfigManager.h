#pragma once 

#include "stdafx.h"

class CConfigManager
{
public:
	//
	//一些全局的配置
	static int nMaxConnectItem;		//最大连接数

private:

public:
	static int GetMaxConnectItem()
	{
		if( -1==nMaxConnectItem )
		{
			ReadMaxConnectItem();
		}
		return nMaxConnectItem;
	}

	static void ReadRouteMain(int *pCPUNumberOf);
	static void ReadRouteUDPListen(int nIndex, int *pPorts, unsigned long *pIP);
	static void ReadRouteRand(int *pMaxServerPeople);
	static void ReadRouteTCPListen(int *pPorts, unsigned long *pIP);

private:
	//
	//一些全局的配置
	static void ReadMaxConnectItem();

};