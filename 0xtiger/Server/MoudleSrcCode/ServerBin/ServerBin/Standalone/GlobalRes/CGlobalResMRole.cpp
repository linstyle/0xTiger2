#include "CGlobalResMRole.h"
#include "../../CConfigManager.h"

CGlobalResMRole GlobalResMRole;


CGlobalResMRole::CGlobalResMRole()
{
	Init();
	TracerMe();
}

void CGlobalResMRole::TracerMe()
{
	printf("\nCGlobalResMRole::TracerMe()\n");

	printf("MaxMRole:%d		FreeMRle:%d		UseMRole:%d\n", CConfigManager::GetMaxMRoleCount(), m_MRoleList.GetSumElementFree(), m_MRoleList.GetSumElementUse());
}

void CGlobalResMRole::Init()
{
	int nMax = CConfigManager::GetMaxMRoleCount();
	m_MRoleList.ManualAlloct( nMax );

	MRoleList_t *p = m_MRoleList.GetListFreeHead();
	for(int i=0; i<nMax; ++i)
	{
		p->element.MRoleHead.InGlobalResMRole.nResIdenti = i;
		p=p->pNext;
	}

}

CMRole* CGlobalResMRole::Add()
{
	return m_MRoleList.GetMallocElement();
}

void CGlobalResMRole::Erase(CMRole* pMRole)
{
	MRoleList_t *p = m_MRoleList.GetElementAtID(pMRole->MRoleHead.InGlobalResMRole.nResIdenti);
	if( NULL==p )
	{
		printf("Warning, CGlobalResMRole::Erase: NULL==p. id:%d\n", pMRole->MRoleHead.InGlobalResMRole.nResIdenti);
		return;
	}

	m_MRoleList.Erase(p);
}