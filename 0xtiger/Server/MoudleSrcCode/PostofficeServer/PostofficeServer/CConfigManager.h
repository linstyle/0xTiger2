#pragma once 

#include "stdafx.h"

class CConfigManager
{
public:

private:

public:
	CConfigManager();

	/*
		��������Ϣ

		GetMaxConnectItem:	ȡ���������������
		GetGlobalIdenti:	ȡ������������������У��ʾ����Ψһ��ʶ
	*/
	static int GetMaxConnectItem(); 
	static int GetGlobalIdenti();
	
	/*
		����ģ��
	*/
	static void ReadConnectPostofficeRoute(int *pPorts, unsigned long *pIP);
	static void ReadPlayIOCPLocal(int *pPorts, unsigned long *pIP);
	static void ReadServerSelfInfo( int *pServerIdenti );
	static void ReadGameInfo(int *pLineNumberOf, int *pMaxBinCount);

private:
	static void ReadMaxConnectItem();
	static void ReadGlobalIdenti();


};