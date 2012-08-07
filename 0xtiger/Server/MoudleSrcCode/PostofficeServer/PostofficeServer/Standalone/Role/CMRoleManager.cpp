#include "CMRoleManager.h"
#include "../../CConfigManager.h"

CMRoleManager::CMRoleManager():nMRoleMaxElement( CConfigManager::GetMaxConnectItem() )
{
	Init();
	nMRoleSumUse = 0;
	nMRoleSumFree =nMRoleMaxElement;
}

CMRoleManager::~CMRoleManager()
{
	delete []m_pMRole;
}

bool CMRoleManager::Init()
{
	m_pMRole = new CMRole[CConfigManager::GetMaxConnectItem()];

	return true;
}

CMRole* CMRoleManager::MRoleAdd( int nIdenti )
{
	if( nIdenti>=nMRoleMaxElement )
	{
		return NULL;
	}

	CMRole *pMRole = &m_pMRole[nIdenti];
	pMRole->Open();

	CounterTick(0);

	return pMRole;
}

int CMRoleManager::MRoleErase(int nIdenti)
{
	if( nIdenti>=nMRoleMaxElement )
	{
		return -1;
	}

	CounterTick(1);

	return m_pMRole[nIdenti].Close();
}

CMRole* CMRoleManager::GetMRoleElementByIdenti( int nIdenti )
{
	if( nIdenti>=nMRoleMaxElement )
	{
		return NULL;
	}

	return &m_pMRole[nIdenti];
}


int CMRoleManager::GetMRoleSumUse()
{	
#ifdef _DEBUG
	int nSumUse=0;	
	for(int i=0; i<nMRoleMaxElement; ++i)
	{
		if( m_pMRole[i].MRoleHead.GetMRoleRunState()!=name_mrole_head::RUN_STATE_DEAD )
		{
			++nSumUse;
		}
	}

	return nSumUse;
#endif

	return nMRoleSumUse;
}

int CMRoleManager::GetMRoleSumFree()
{
#ifdef _DEBUG
	int nSumFree=0;	
	for(int i=0; i<nMRoleMaxElement; ++i)
	{
		if( m_pMRole[i].MRoleHead.GetMRoleRunState()==name_mrole_head::RUN_STATE_DEAD )
		{
			++nSumFree;
		}		
	}

	return nSumFree;
#endif

	return nMRoleSumFree;
}