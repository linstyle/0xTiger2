#include "StdAfx.h"
#include "Exception.h"
#include "../Logic/Role/CRoleAllocator.h"

initialiseSingleton(PExceptionObject);

int	PExceptionObject::Execute(IPackHead* pPackHead, void* pRole)
{
	g_RoleAllocator.FreeRoleObject((CRole*)pRole);
	return 0;
}
