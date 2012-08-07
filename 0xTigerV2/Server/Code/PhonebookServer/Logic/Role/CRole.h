/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                        
    功能说明：  逻辑对象，或者称为人物
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
