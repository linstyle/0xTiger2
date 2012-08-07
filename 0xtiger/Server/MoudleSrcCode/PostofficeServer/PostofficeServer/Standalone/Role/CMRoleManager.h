#pragma once

#include "CMRole.h"

/*
   管理MROLE数组的对象池，根据ID来进行分配和返回。
   所谓的分配和释放指的是MROLE的__nMRoleRunState状态.
   如果是RUN_STATE_DEAD表示空闲，否则反之

*/

class CMRoleManager
{
public:
	
	
private:
	CMRole *m_pMRole;
	const int nMRoleMaxElement;
	int nMRoleSumUse;
	int nMRoleSumFree;

public:
	CMRoleManager();
	~CMRoleManager();

	bool Init();

	/*
		开放的接口：增，删，查询
	*/
	CMRole* MRoleAdd( int nIdenti );
	int MRoleErase(int nIdenti);
	CMRole* GetMRoleElementByIdenti( int nIdenti );

	int GetMRoleSumUse();
	int GetMRoleSumFree();

private:
	/*
		计数器加减
		0 增加MROLE
		1 释放MROLE
	*/
	void CounterTick(int nAddOrErase)
	{
		switch (nAddOrErase)
		{
		case 0:
			++nMRoleSumUse;
			--nMRoleSumFree;
			break;
		case 1:
			--nMRoleSumUse;
			++nMRoleSumFree;
			break;
		default:
			break;
		}
	}

};