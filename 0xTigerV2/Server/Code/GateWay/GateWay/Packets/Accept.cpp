#include "StdAfx.h"
#include "Accept.h"
#include "../Logic/Role/CRoleAllocator.h"

initialiseSingleton(PAcceptObject);

int	PAcceptObject::Execute(IPackHead* pPackHead, void* pRoleObject)
{	
	CRole *pRole = g_RoleAllocator.MallocRoleObject();
	pRole->SetRoleNet( (CIOCPData*)pRoleObject );

	return (int)pRole;		
}


