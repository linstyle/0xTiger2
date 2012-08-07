#pragma once 

#include "stdafx.h"

class CConfigManager
{
public:
	//
	//һЩȫ�ֵ�����
	static int nMaxConnectItem;		//���������

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
	//һЩȫ�ֵ�����
	static void ReadMaxConnectItem();

};