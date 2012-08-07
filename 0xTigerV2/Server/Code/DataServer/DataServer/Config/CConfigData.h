/*  作者：		林东平                                                              
	创建时间：	2011/02/28                                                         
    功能说明：  游戏中需要使用的外配数据结构。从配置文件中抽象出来，不受
				外部数据的改变而改变
*/

#pragma  once

/*
	DataServer的网络配置信息
*/
struct DATA_SERVER_NET
{
	DATA_SERVER_NET();
	~DATA_SERVER_NET();

	int nGateWayCount;				//需要连接的网关数
	unsigned long *pGateWayIP;		//IP
	int *pGateWayPort;				//端口
	int nAcceptPort;				//本地的Accept端口
};

/*
	网关的GUID配置信息
*/
struct DATA_SERVER_GUID
{
	DATA_SERVER_GUID();
	unsigned int GUID_HUMAN_BEGIN;
	unsigned int GUID_HUMAN_END;

	unsigned int GUID_ITEM_BEGIN;
	unsigned int GUID_ITEM_END;

	unsigned int GUID_MONSTER_BEGIN;
	unsigned int GUID_MONSTER_END;
};