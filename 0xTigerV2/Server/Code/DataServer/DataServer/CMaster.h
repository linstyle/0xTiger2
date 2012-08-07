/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                       
    功能说明：  DataServer,main函数管理
*/

#pragma once

#include "Singleton.h"
/*
	工程本地单例
*/
#include "Net/CNetMaster.h"


class CMaster:public Singleton<CMaster>
{
public:
	CMaster();
	~CMaster();

	void Init();
	bool Loop();
	void Exit();
private:

public:

private:
	CNetMaster m_NetMaster;
	
};

#define g_Master CMaster::getSingleton()