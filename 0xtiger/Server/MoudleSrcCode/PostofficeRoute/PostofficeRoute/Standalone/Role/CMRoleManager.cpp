#include "CMRoleManager.h"
#include "../../CConfigManager.h"

CMRoleManager::CMRoleManager():m_nMRoleMaxElement( CConfigManager::GetMaxConnectItem() )
{
	Init();
}

CMRoleManager::~CMRoleManager()
{
	
}

bool CMRoleManager::Init()
{
	m_MRoleList.ManualAlloct( m_nMRoleMaxElement );

	Element_t *p = m_MRoleList.GetListFreeHead();
	for(int i=0; i<m_nMRoleMaxElement; ++i)
	{
		p->element.MRoleHead.InMRoleManager.nResIdenti = i;
		p=p->pNext;
	}
	return true;
}

CMRole* CMRoleManager::MRoleAdd( int nNetKey )
{
	/*
		如果分配对象成功，则产生映射关系
	*/
	CMRole *p = AddToMRoleSet();
	if( NULL==p )
	{
		return NULL;
	}

	AddToMRoleMap(nNetKey, p);

	return p;
}

void CMRoleManager::MRoleErase(int nNetKey)
{
	CMRole *p = EraseFromMRoleMap(nNetKey);
	if( p==NULL )
	{
		printf("Warning, CMRoleManager::MRoleErase: NULL==p. nNetKey:%d\n", nNetKey);				
	}

	EraseFromMRoleSet(p);

}
/*
CMRoleManager::CMRole * CMRoleManager::MRoleErase(CMRole * pElement, int nNetKey)
{
	CMRoleManager::Element_t *p = EraseFromMRoleMap(nNetKey);
	if( p!=pElement || NULL==p )
	{
		return NULL;
	}
	return EraseFromMRoleSet(p);
}
*/
CMRole* CMRoleManager::GetMRoleByNetKey( int nNetKey)
{
	CMRole * p = NULL;
	
	IterMap_t Iter;

	Iter = MRoleMap.find(nNetKey);
	if( Iter!=MRoleMap.end() )
	{
		p = Iter->second;		
	}
	
	return p;
}



CMRole* CMRoleManager::AddToMRoleSet()
{
	return m_MRoleList.GetMallocElement();
}

void CMRoleManager::EraseFromMRoleSet(CMRole* pMRole)
{
	Element_t *p = m_MRoleList.GetElementAtID( pMRole->MRoleHead.InMRoleManager.nResIdenti );
	if( NULL==p )
	{
		printf("Warning, CMRoleManager::EraseFromMRoleSet: NULL==p. id:%d\n",  pMRole->MRoleHead.InMRoleManager.nResIdenti);
		return;	
	}
	m_MRoleList.Erase(p);
}

void CMRoleManager::AddToMRoleMap(int nNetKey, CMRole * pMRole)
{
	MRoleMap.insert( pair<int, CMRole* >(nNetKey, pMRole) );
}

CMRole * CMRoleManager::EraseFromMRoleMap(int nNetKey)
{
	CMRole * p = NULL;
	IterMap_t Iter;

	Iter = MRoleMap.find(nNetKey);
	if( Iter!=MRoleMap.end() )
	{
		p = Iter->second;
		MRoleMap.erase(Iter);
	}
	
	return p;
}

int CMRoleManager::GetMRoleSumUse()
{	
	return m_MRoleList.GetSumElementUse();
}

int CMRoleManager::GetMRoleSumFree()
{
	return m_MRoleList.GetSumElementFree();
}