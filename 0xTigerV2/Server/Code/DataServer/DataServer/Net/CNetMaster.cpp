#include "stdafx.h"
#include "CNetMaster.h"
#include "CNetDriver.h"
#include "../Config/CConfigRead.h"

#include "PLoginGateWay.h"

void CNetMaster::Init()
{
	m_NetAccept.Init();
	InitConnectGateWay();

	//add to NetDriver
	g_NetDriver.Init(m_pConnectGateWay, m_nConnectGateWayCount, &m_NetAccept, 1);

	LoginGateWay();
}

CNetMaster::~CNetMaster()
{
	delete []m_pConnectGateWay;
}

void CNetMaster::InitConnectGateWay()
{
	DATA_SERVER_NET *pDataServerNet = g_ConfigRead.GetDataServerNet();
	m_nConnectGateWayCount = pDataServerNet->nGateWayCount;

	m_pConnectGateWay = new CNetConnectGateWay[m_nConnectGateWayCount];

	char Buff[32];
	for(int i=0; i<m_nConnectGateWayCount; ++i)
	{
		memset(Buff, 0, 32);
		sprintf(Buff, "ConectGateWay_%d", i);
		m_pConnectGateWay[i].Init(Buff, pDataServerNet->pGateWayIP[i], pDataServerNet->pGateWayPort[i]);
	}
}

void CNetMaster::LoginGateWay()
{
	PLoginDG LoginDG;

	for(int i=0; i<m_nConnectGateWayCount; ++i)
	{
		//m_pConnectGateWay[i]
		if( -1==g_NetDriver.Send(m_pConnectGateWay[i].GetIOCPData(), &LoginDG))
		{
			LOG(LOG_ERROR, "CNetMaster::LoginGateWay(), Send LoginDG\n");
		}
	}

	
}