/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/22                                                         
    ����˵����  �ù��������ļ��Ķ�ȡ

	�޸� 2011/2/28
			���ϵ�ȫ�ֵ����ù���,��������ݽṹ
*/

#pragma once

#include "MTVERIFY.h"
#include "CConfigData.h"
#include "Singleton.h"

class CConfigRead:public Singleton<CConfigRead>
{
public:
	CConfigRead();

	void Init();
	
	GATEWAY_NET* GetGateWayNet();
	GATEWAY_GUID* GetGeteWayGUID();
private:
	//���ڷ��������������
	void ReadGateWayServer();

	//GUIDֵ
	void ReadGateWayGUID();

public:

private:
	GATEWAY_NET m_GateWayNet;
	GATEWAY_GUID m_GateWayGUID;

};

#define g_ConfigRead CConfigRead::getSingleton()