/*
	按
	线1:{场景服务器1,场景服务器2......}

	线2:{场景服务器1,场景服务器2......}

	线3:{场景服务器1,场景服务器2......}
	来记录结构
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
	int nSocket;		//可以使用getsockname来取得sockaddr信息
	int nIdenti;		//场景编号
	int nMRoleSum;		//玩家总数, dpc服务器不用到这个字段
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
		几条线
		游戏共有多少场景服务器
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
		
		返回一个套接字		
	*/
	int GetBinSocketByIdenti(int nLine, int nBinIdenti);
	int GetDpcSocket();

private:
	void Init();

	void ReadFromConfigManager();

	/*
		ServerIdentiVerify
		检测所请求的场景对象是否正确
	*/
	LOGIC_SERVER_BIN * BinVerifyIdenti(int nLine, int nBinIdenti);

};