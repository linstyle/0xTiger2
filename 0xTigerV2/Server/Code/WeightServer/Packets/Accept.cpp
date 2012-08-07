#include "StdAfx.h"
#include "Accept.h"
#include "../Logic/Role/CRoleAllocator.h"

initialiseSingleton(PAcceptObject);

int	PAcceptObject::Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet)
{
	static int i=0;
	CRole *pRole = g_RoleAllocator.MallocRoleObject();

	pRole->m_nRoleID = i++;

	return (int)pRole;		
}


