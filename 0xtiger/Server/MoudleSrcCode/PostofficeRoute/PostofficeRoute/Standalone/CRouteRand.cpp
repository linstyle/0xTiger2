#include "CRouteRand.h"

CRouteRand g_RouteRand;

//
//debug tracer
void CRouteRand::TracerMe()
{	
	printf("CRouteRand:TracerMe---------------------\n");
	printf("nMaxServerPeople:%d\n", nMaxServerPeople);	
}

void CRouteRand::TracerMe_All()
{
	printf("CRouteRand::TracerMe_All:---------------------\n");

	int nMaxItem = CConfigManager::GetMaxConnectItem();
	for(int i=0; i<nMaxItem; ++i)
	{
		printf("index:%d	sum people:%d	ip:%s	port:%d	\n", 
			    i, m_pServerInfo[i].nSumPeople, 
				inet_ntoa( *( (in_addr*)&m_pServerInfo[i].nIP) ), m_pServerInfo[i].nPort);
	}
	
	printf("\n");
}

//
//construct
//
CRouteRand::CRouteRand()
{
	nSumServerPeople = nMaxServerPeople = 0;
	
	int nMaxItem = CConfigManager::GetMaxConnectItem();

	m_pServerInfo = new SERVER_INFO[nMaxItem];
	m_pServerSelectRecord = new int[nMaxItem];
	m_pServerProportion = new int[nMaxItem];
	m_pServerProportionOffset =new int[nMaxItem];

	memset(m_pServerProportion, 0, sizeof(int)*nMaxItem );
	memset(m_pServerProportionOffset, 0, sizeof(int)*nMaxItem );
	memset(m_pServerSelectRecord, 0, sizeof(int)*nMaxItem );

	Init();
	TracerMe();

	CtrlProportion();
}

CRouteRand::~CRouteRand()
{
	delete []m_pServerInfo;
	delete []m_pServerSelectRecord;
	delete []m_pServerProportion;
	delete []m_pServerProportionOffset;
}

//
//public
//
bool CRouteRand::Init()
{
	bool bResult=false;

	ReadFromConfigManager();

	return bResult;
}

const SERVER_INFO* CRouteRand::GetRandObject()
{
	srand(GetTickCount());
	int nRandValue = rand()%name_route_rand::PEOPLE_PRICISION_PROPORTION ;

	for(int i=0; i<CConfigManager::GetMaxConnectItem(); ++i)
	{
		int nBegin = m_pServerProportionOffset[i] - m_pServerProportion[i];
		int nEnd = m_pServerProportionOffset[i];

		if( (nRandValue>=nBegin) && (nRandValue<nEnd) )
		{
			return &m_pServerInfo[i];
		}
	}

	return NULL;
}

SERVER_INFO* CRouteRand::GetServerObject(int nIndex)
{
	return &m_pServerInfo[nIndex];
}

//
//private
//

void CRouteRand::ReadFromConfigManager()
{
	CConfigManager::ReadRouteRand(&nMaxServerPeople);
}


//
//先求出当前/总值的比例，再以当前的值总和作为分母
void CRouteRand::CtrlProportion()
{
	int i;
	int nSumServerProportion=0;
	
	for(i=0; i<CConfigManager::GetMaxConnectItem(); ++i)
	{ 		
		//
		//判断是否超出单台上限或者当前对应的连接无效
		if( nMaxServerPeople<m_pServerInfo[i].nSumPeople || false==m_pServerInfo[i].nEnable)
		{
			m_pServerProportion[i] = 0;
		}
		else
		{				
			m_pServerProportion[i] = (nMaxServerPeople-m_pServerInfo[i].nSumPeople) / 
				           (double)nMaxServerPeople * name_route_rand::PEOPLE_PRICISION_PROPORTION;		
		}

		nSumServerProportion += m_pServerProportion[i];
	}

	for(i=0; i<CConfigManager::GetMaxConnectItem(); ++i)
	{		
		m_pServerProportion[i] = m_pServerProportion[i] / 
			              (double)nSumServerProportion * name_route_rand::PEOPLE_PRICISION_PROPORTION;
	}

	m_pServerProportionOffset[0] = m_pServerProportion[0];
	for(i=1; i<CConfigManager::GetMaxConnectItem(); ++i)
	{
		m_pServerProportionOffset[i] = m_pServerProportionOffset[i-1] + m_pServerProportion[i];
	}
}
