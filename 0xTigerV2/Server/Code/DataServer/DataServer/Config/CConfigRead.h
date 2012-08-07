/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/22                                                         
    ����˵����  �ù��������ļ��Ķ�ȡ

	�޸� 2011/2/28
			���ϵ�ȫ�ֵ����ù���,��������ݽṹ
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
	//���ڷ��������������
	void ReadDataServer();

	//GUIDֵ
	void ReadDataServerGUID();

public:

private:
	DATA_SERVER_NET m_DataServerNet;
	DATA_SERVER_GUID m_DataServerGUID;

};

#define g_ConfigRead CConfigRead::getSingleton()