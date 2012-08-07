/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                       
    ����˵����  DataServer,main��������
*/

#pragma once

#include "Singleton.h"
/*
	���̱��ص���
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