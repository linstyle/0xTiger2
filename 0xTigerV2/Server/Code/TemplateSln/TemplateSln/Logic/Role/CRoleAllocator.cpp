#include "StdAfx.h"
#include "CRoleAllocator.h"

initialiseSingleton(CRoleAllocator);

CRoleAllocator::CRoleAllocator()
{
	 
}


CRole* CRoleAllocator::MallocRoleObject()
{
	void *p = g_KmemManager.KmemMalloc(sizeof(CRole));	

	if( NULL==p )
	{
		return NULL;
	}

	CRole *pRole = new(p)CRole;

	return pRole;
}


void CRoleAllocator::FreeRoleObject(CRole *pRole)
{
	/*
		����C++����ԭ������������������
	*/
	pRole->~CRole();
	g_KmemManager.KmemFree((void*)pRole);	
}