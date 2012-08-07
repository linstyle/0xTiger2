#pragma once 

#include "stdafx.h"

class CConfigManager
{
public:

private:

public:
	CConfigManager();

	/*
		程序本身信息

		GetMaxConnectItem:	取得最大允许连接数
		GetGlobalIdenti:	取得在整个服务器组件中，邮局组的唯一标识
	*/
	static int GetMaxConnectItem(); 
	static int GetGlobalIdenti();
	
	/*
		其他模块
	*/
	static void ReadConnectPostofficeRoute(int *pPorts, unsigned long *pIP);
	static void ReadPlayIOCPLocal(int *pPorts, unsigned long *pIP);
	static void ReadServerSelfInfo( int *pServerIdenti );
	static void ReadGameInfo(int *pLineNumberOf, int *pMaxBinCount);

private:
	static void ReadMaxConnectItem();
	static void ReadGlobalIdenti();


};