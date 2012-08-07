/*  作者：		林东平                                                              
	创建时间：	2011/03/08                                                         
    功能说明：  网络模块管理
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
		发送登陆信息
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
