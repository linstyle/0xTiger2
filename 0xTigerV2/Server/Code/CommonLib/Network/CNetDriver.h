/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/14                                                         
    ����˵����  �Եײ������һ���ӿڷ�װ
				ע���³�ʼ��˳���ȸ���Add��Ȼ�����Fire()�����������ִ���ⲿ�ӿ���Run();
*/

#pragma once

#include <vector>

#include "GlobalType.h"
#include "Singleton.h"
#include "CSocketRun.h"

class CNetDriver: public Singleton<CNetDriver>
{
public:
	void TracerMe();
	void Tracer();
		
	void Init(ILocalObjectConnect* pObjectConnect, int nConnectCount, 
			  ILocalObjectAccept* pObjectAccept, int nAcceptCount);

	void Run();
	int Send(CIOCPData *pIOCPKey, IPackHead *pPackHead);
private:

public:

private:
	CSocketRun m_SocketRun;

};



#define g_NetDriver CNetDriver::getSingleton()