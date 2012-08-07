/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                        
    功能说明：  逻辑对象分配器
*/

#pragma once
#include "Singleton.h"
#include "CRole.h"
#include "CSlab.h"

class CRoleAllocator:public Singleton<CRoleAllocator>
{
public:
	CRoleAllocator();

	/*
		对象缓冲池的一个封装
	*/
	CRole* MallocRoleObject();	
	void FreeRoleObject(CRole *pRole);

private:

public:

private:

};

#define g_RoleAllocator CRoleAllocator::getSingleton()