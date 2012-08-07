#include "StdAfx.h"
#include "CRole.h"

void CRole::SetRoleNet(CIOCPData *pRoleNet)
{
	m_pRoleNet = pRoleNet;
}

CIOCPData* CRole::GetRoleNet()
{
	return m_pRoleNet;
}

CRoleLogic* CRole::GetRoleLogic()
{
	return &m_RoleLogic;
}