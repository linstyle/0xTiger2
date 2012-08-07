#pragma once
/*
按比例取得随机对象
*/

/*
Rand主要维护对一个int数组进行随机。而外部可能需要更多的信息。
因此，外部数据结构里保持有提供给rand的int数组即可.并且，SERVER_INFO这个数组里
保持静态不变，这样当rand找到int时，可以直接根据当前索引定位到
*/
#include "../stdafx.h"
#include "../CConfigManager.h"

namespace name_route_rand
{
	//
	//最大支持的邮局服务器数，这里为静态分配.莫大于64。	
	const int PEOPLE_PRICISION_PROPORTION = 1000;
};

//
//外部需要的信息结构
//这里的结构体内容和数量都和CRouteServerTCP中保持一致，以作为对应关系
struct SERVER_INFO
{
	SERVER_INFO()
	{	
		nEnable = false;
		nSocket = nPort = nIP = nSumPeople = 0;		
	}
	bool nEnable;
	int nPort;
	unsigned long nIP;		//TCP/IP network byte order
	int nSumPeople;			//CRouteRand必须的要素

	//
	//debug
	int nSocket;			//判断是否有断连的痕迹
};

class CRouteRand
{
public:
	int *m_pServerSelectRecord;
	SERVER_INFO *m_pServerInfo;

private:	
	int nSumServerPeople;
	int nMaxServerPeople;			//was read from config
	int *m_pServerProportion;
	int *m_pServerProportionOffset;
	
public:
	CRouteRand();
	~CRouteRand();

	bool Init();

	void CtrlProportion();
	const SERVER_INFO* GetRandObject();
	SERVER_INFO* GetServerObject(int nIndex);
	
	void EnableServerInfo(int i)
	{
		m_pServerInfo[i].nSumPeople = 0;
	}
	void DisableServerInfo(int i)
	{
		m_pServerInfo[i].nSumPeople = 0;	
	}


private:
	//
	//Debug Tracer
	void TracerMe();
	//
	//Init
	void ReadFromConfigManager();	

//debug
public:
	void TracerMe_All();
};