#include "StdAfx.h"
#include "Exception.h"
#include "../Logic/Role/CRoleAllocator.h"

initialiseSingleton(PExceptionObject);


int	PExceptionObject::Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet)
{
	g_RoleAllocator.FreeRoleObject((CRole*)pPlayLogic);
	return 0;
}
