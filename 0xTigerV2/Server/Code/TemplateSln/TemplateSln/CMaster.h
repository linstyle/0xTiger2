/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                       
    ����˵����  TemplateSln, main��������
*/

#pragma once

#include "Singleton.h"

#include "Net/CNetConnect.h"


/*
	�ļ��������
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
		main�����ı���
	*/
	CNetConnect NetConnect;
	CDemoTransFile DemoTransFile;

	PFileTrans m_FileTrans;
	bool m_bLastTransSucceed;
};

#define g_Master CMaster::getSingleton()