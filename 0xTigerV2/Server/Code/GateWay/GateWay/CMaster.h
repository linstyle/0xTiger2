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

	void Init();
	bool Loop();
	void Exit();
private:

public:

private:
	/*
		main�����ı���
	*/

	CNetAccept m_NetAccept;
	
};

#define g_Master CMaster::getSingleton()