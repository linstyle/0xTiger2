/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                        
    ����˵����  �߼����󣬻��߳�Ϊ����
*/
#pragma once

#include "CRoleLogic.h"
#include "CNetObject.h"

class CRole
{
public:
	void SetRoleNet(CIOCPData *pRoleNet);
	CIOCPData* GetRoleNet();

	CRoleLogic* GetRoleLogic();
private:

public:

private:
	CRoleLogic m_RoleLogic;
	CIOCPData  *m_pRoleNet;
};
