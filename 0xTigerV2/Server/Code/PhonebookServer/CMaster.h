/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                       
    ����˵����  PhonebookServer,main��������
*/

#pragma once

#include "Singleton.h"
/*
	���̱��ص���
*/
#include "Net/CNetAccept.h"


class CMaster:public Singleton<CMaster>
{
public:
	CMaster();
	~CMaster();

	void ServerInit();
	bool ServerLoop();
	void ServerExit();
private:

public:

private:
	/*
		main�����ı���
	*/

	CNetAccept NetAccept;
	
};

#define g_Master CMaster::getSingleton()