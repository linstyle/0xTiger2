/*  作者：		林东平                                                              
	创建时间：	2010/07/22                                                         
    功能说明：  该工程配置文件的读取

	修改 2011/2/28
			整合到全局的配置管理,抽象出数据结构
*/

#pragma once

#include "MTVERIFY.h"
#include "CConfigData.h"
#include "Singleton.h"

class CConfigRead:public Singleton<CConfigRead>
{
public:
	CConfigRead();

	void Init();
	
	GATEWAY_NET* GetGateWayNet();
	GATEWAY_GUID* GetGeteWayGUID();
private:
	//关于服务器本身的配置
	void ReadGateWayServer();

	//GUID值
	void ReadGateWayGUID();

public:

private:
	GATEWAY_NET m_GateWayNet;
	GATEWAY_GUID m_GateWayGUID;

};

#define g_ConfigRead CConfigRead::getSingleton()