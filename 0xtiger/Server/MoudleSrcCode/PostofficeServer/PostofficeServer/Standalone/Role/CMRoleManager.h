#pragma once

#include "CMRole.h"

/*
   ����MROLE����Ķ���أ�����ID�����з���ͷ��ء�
   ��ν�ķ�����ͷ�ָ����MROLE��__nMRoleRunState״̬.
   �����RUN_STATE_DEAD��ʾ���У�����֮

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
		���ŵĽӿڣ�����ɾ����ѯ
	*/
	CMRole* MRoleAdd( int nIdenti );
	int MRoleErase(int nIdenti);
	CMRole* GetMRoleElementByIdenti( int nIdenti );

	int GetMRoleSumUse();
	int GetMRoleSumFree();

private:
	/*
		�������Ӽ�
		0 ����MROLE
		1 �ͷ�MROLE
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