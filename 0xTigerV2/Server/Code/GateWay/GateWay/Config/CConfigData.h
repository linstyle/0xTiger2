/*  作者：		林东平                                                              
	创建时间：	2011/02/28                                                         
    功能说明：  游戏中需要使用的外配数据结构。从配置文件中抽象出来，不受
				外部数据的改变而改变
*/

#pragma  once

/*
	网关的网络配置信息
*/
struct GATEWAY_NET
{
	GATEWAY_NET();
	int nAcceptPort;			//本地的Accept端口
	int nMaxConnectClient;//支持最大的客户端个数
	int nMaxConnectChatServer;	//支持最大的聊天服务器个数
	int nMaxConnectDataServer;	//支持最大的Data服务器个数
	
};

/*
	网关的GUID配置信息
*/
struct GATEWAY_GUID
{
	GATEWAY_GUID();
	unsigned int GUID_HUMAN_BEGIN;
	unsigned int GUID_HUMAN_END;

	unsigned int GUID_ITEM_BEGIN;
	unsigned int GUID_ITEM_END;

	unsigned int GUID_MONSTER_BEGIN;
	unsigned int GUID_MONSTER_END;
};