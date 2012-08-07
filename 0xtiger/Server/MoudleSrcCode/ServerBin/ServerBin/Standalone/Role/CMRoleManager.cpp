#include "CMRoleManager.h"
#include "../../CConfigManager.h"

#include "../GlobalRes/CGlobalResMRole.h"
extern CGlobalResMRole GlobalResMRole;

CMRoleManager::CMRoleManager()
{
	Init();

}

CMRoleManager::~CMRoleManager()
{
	
}

void CMRoleManager::Init()
{

}

void CMRoleManager::CallBackTracerMe()
{
	printf("\nCMRoleManager::CallBackTracerMe\n");
	printf("MRoleSumUse:%d		MRoleSumFree:%d\n", GetMRoleSumUse(), GetMRoleSumFree());
}


CMRole* CMRoleManager::MRoleAdd()
{
	CMRole *p = GlobalResMRole.Add();
	if( NULL==p )
	{
		return NULL;
	}

	m_UserList.insert( pair<CMRole*, CMRole*>(p, p) );
	return p;
}

CMRole* CMRoleManager::MRoleErase(CMRole *pMRole, int nFromGlobalResMRole)
{
	IterMap_t Iter;

	Iter = m_UserList.find( pMRole);

	if( Iter==m_UserList.end() )
	{
		printf("Warning, CGlobalResMRole::Erase: NULL==p\n");
		return pMRole;		
	}

	m_UserList.erase(Iter);

	if( 1==nFromGlobalResMRole )
	{
		GlobalResMRole.Erase(pMRole);
	}

	return pMRole;
}

int CMRoleManager::GetMRoleSumUse()
{	
	return m_UserList.size();
}

int CMRoleManager::GetMRoleSumFree()
{
	//return m_UserList.GetSumElementFree();
	return 0;
}