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
		根据C++对象原则，主动调用析构函数
	*/
	pRole->~CRole();
	g_KmemManager.KmemFree((void*)pRole);	
}