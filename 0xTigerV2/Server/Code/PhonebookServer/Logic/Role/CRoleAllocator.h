/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                        
    ����˵����  �߼����������
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
		���󻺳�ص�һ����װ
	*/
	CRole* MallocRoleObject();	
	void FreeRoleObject(CRole *pRole);

private:

public:

private:

};

#define g_RoleAllocator CRoleAllocator::getSingleton()