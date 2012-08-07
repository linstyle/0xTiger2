/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                       
    功能说明：  PhonebookServer,main函数管理
*/

#pragma once

#include "Singleton.h"
#include "CCmInitSingleton.h"

/*
	工程本地单例
*/
#include "Net/CNetConnect.h"
#include "Logic/Role/CRoleAllocator.h"

#include "Packets/Exception.h"
#include "Packets/Accept.h"
#include "Packets/HelloWorld.h"


const int CONNECT_COUNT =300;

class CMaster:public Singleton<CMaster>
{
public:
	CMaster()
	{
		ServerInit();
	}
	~CMaster()
	{
		ServerExit();
	}

	void ServerInit();
	bool ServerLoop();
	void ServerExit();
private:

public:

private:
	CNetConnect m_NetConnect[CONNECT_COUNT];
	
};

#define g_Master CMaster::getSingleton()