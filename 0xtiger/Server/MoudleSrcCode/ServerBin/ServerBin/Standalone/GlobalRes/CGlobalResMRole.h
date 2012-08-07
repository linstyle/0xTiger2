/*
	全局的玩家对象池管理

	供应各个场景的人物内存需求
*/
#pragma once

#include "../Role/CMRole.h"
#include "Algorithm/CListOfArray.h"

class CGlobalResMRole
{
public:
	CListOfArray<CMRole, 0, true> m_MRoleList;
	typedef CListOfArray<CMRole, 0, true>::ELEMENT MRoleList_t;

private:
	void TracerMe();

public:
	CGlobalResMRole();
	void Init();

	CMRole* Add();
	void Erase(CMRole* pMRole);

private:

};