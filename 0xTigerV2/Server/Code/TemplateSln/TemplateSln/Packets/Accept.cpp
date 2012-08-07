#include "StdAfx.h"
#include "Accept.h"
#include "../Logic/Role/CRoleAllocator.h"

initialiseSingleton(PAcceptObject);

int	PAcceptObject::Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet)
{
	CRole *pRole = g_RoleAllocator.MallocRoleObject();

	return (int)pRole;		
}


