/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                       
    功能说明：  TemplateSln, main函数管理
*/

#pragma once

#include "Singleton.h"

#include "Net/CNetConnect.h"


/*
	文件传输测试
*/
#include "Logic/CDemoTransFile.h"

class CMaster:public Singleton<CMaster>
{
public:
	CMaster();
	~CMaster();

	void ServerInit();
	bool ServerLoop();
	void ServerExit();

private:
	bool TransFile();

public:

private:
	/*
		main函数的变量
	*/
	CNetConnect NetConnect;
	CDemoTransFile DemoTransFile;

	PFileTrans m_FileTrans;
	bool m_bLastTransSucceed;
};

#define g_Master CMaster::getSingleton()