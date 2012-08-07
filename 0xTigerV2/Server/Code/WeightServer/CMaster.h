/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                       
    ����˵����  PhonebookServer,main��������
*/

#pragma once

#include "Singleton.h"
#include "CCmInitSingleton.h"

/*
	���̱��ص���
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