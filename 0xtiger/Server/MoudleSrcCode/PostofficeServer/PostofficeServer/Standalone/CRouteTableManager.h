/*
	��
	��1:{����������1,����������2......}

	��2:{����������1,����������2......}

	��3:{����������1,����������2......}
	����¼�ṹ
*/
#pragma once
#include <stdio.h>
#include "../CConfigManager.h"


struct LOGIC_SERVER_BIN
{
	LOGIC_SERVER_BIN()
	{
		bEnable = false;
		nIdenti = -1;
		nMRoleSum = -1;
	}

	bool bEnable;
	int nSocket;		//����ʹ��getsockname��ȡ��sockaddr��Ϣ
	int nIdenti;		//�������
	int nMRoleSum;		//�������, dpc���������õ�����ֶ�
};


struct LOGIC_SERVER_LINE
{
	~LOGIC_SERVER_LINE()
	{
		delete[] pScene;
	}

	int nLine;
	LOGIC_SERVER_BIN *pScene;
};


class CRouteTableManager
{
public:
	LOGIC_SERVER_LINE *pLogicServerBin;
	LOGIC_SERVER_BIN LogicServerDpc;

private:
	/*
		������
		��Ϸ���ж��ٳ���������
	*/
	int nMaxLine;
	int nMaxBinCount;
 
public:
	CRouteTableManager();
	~CRouteTableManager();

	void TracerMe();
	void CallBackTracerMe();
	/*

	*/	
	int BinAdd(int nLine, int nBinIdenti, int nSocket);
	void BinErase(int nLine, int nBinIdenti);
	int DpcAdd(int nSocket);
	/*
		
		����һ���׽���		
	*/
	int GetBinSocketByIdenti(int nLine, int nBinIdenti);
	int GetDpcSocket();

private:
	void Init();

	void ReadFromConfigManager();

	/*
		ServerIdentiVerify
		���������ĳ��������Ƿ���ȷ
	*/
	LOGIC_SERVER_BIN * BinVerifyIdenti(int nLine, int nBinIdenti);

};