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
	*/
	static int GetLineIdenti();
	static int GetGlobalIdenti();
	static int GetMaxPostofficeCount();
	static int GetMaxMRoleCount();

	/*
		其他模块		
	*/
	static void ReadConnectPostofficeServer(int nIndex, int *pPort, unsigned long *pIP);	
	static void ReadSceneSelfInfo(int nIndex, int *pSceneIdenti);
	static void ReadSceneCount(int *pSceneMaxCount);

private:
	static void ReadLineIdenti();
	static void ReadGlobalIdenti();
	static void ReadMaxPostofficeCount();
	static void ReadMaxMRoleCount();

};