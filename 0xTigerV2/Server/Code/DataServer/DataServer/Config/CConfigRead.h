/*  作者：		林东平                                                              
	创建时间：	2010/07/22                                                         
    功能说明：  该工程配置文件的读取

	修改 2011/2/28
			整合到全局的配置管理,抽象出数据结构
*/

#pragma once
#include "GlobalType.h"
#include "MTVERIFY.h"
#include "CConfigData.h"
#include "Singleton.h"

class CConfigRead:public Singleton<CConfigRead>
{
public:
	CConfigRead();

	void Init();
	
	DATA_SERVER_NET* GetDataServerNet();
	DATA_SERVER_GUID* GetDataServerGUID();
private:
	//关于服务器本身的配置
	void ReadDataServer();

	//GUID值
	void ReadDataServerGUID();

public:

private:
	DATA_SERVER_NET m_DataServerNet;
	DATA_SERVER_GUID m_DataServerGUID;

};

#define g_ConfigRead CConfigRead::getSingleton()