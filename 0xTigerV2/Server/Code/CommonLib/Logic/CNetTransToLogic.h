/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/20                                                         
    ����˵����  ���������������߼�.ʹ��������벻�Ե����ͣ���һЩ���������Ե������޸�
*/

#pragma once
#include "Singleton.h"
#include "CPacketFactory.h"
#include "ListArrayMap.h"
#include "CLock.h"

class CNetTransToLogic:public Singleton<CNetTransToLogic>
{
public:
	CNetTransToLogic();
	/*
		���յ�һ���������ӡ������쳣 �����Ĵ���
	*/
	int AcceptConnect(CIOCPData* pIOCPKey);
	int ExceptionPacket(CIOCPData* pIOCPKey);

	/*
		����-1��ʾ�߼���ִ�г����������Ҫ��Ӧ�Ĵ���
	*/
	int ExcutePacket(CIOCPData* pIOCPKey);

private:

public:

private:
	CFastLock m_Lock;
	CListArrayMap<CIOCPData*, void*> m_NetLogicMap;

};

#define g_NetTransToLogic CNetTransToLogic::getSingleton()
