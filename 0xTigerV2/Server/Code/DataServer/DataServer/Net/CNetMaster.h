/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/03/08                                                         
    ����˵����  ����ģ�����
*/

#pragma once
#include "CNetAccept.h"
#include "CNetConnect.h"

class CNetMaster
{
public:
	void Init();
	~CNetMaster();

	/*
		���͵�½��Ϣ
	*/
	void LoginGateWay();

private:	
	void InitConnectGateWay();



public:

private:
	CNetAccept m_NetAccept;
	int m_nConnectGateWayCount;
	CNetConnectGateWay *m_pConnectGateWay;
};
