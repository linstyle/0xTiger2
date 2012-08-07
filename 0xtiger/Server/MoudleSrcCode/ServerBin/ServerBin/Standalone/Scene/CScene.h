#pragma once

#include "../Role/CMRoleManager.h"

class CScene
{
public:
	CMRoleManager MRoleManager;

private:
	int m_nMaxMRoleNow;
	int m_nSceneIdenti;

public:
	void CallBackDoing();
	void CallBackTracerMe();

	void Init(int nSceneIdenti);

	CMRole* MRoleAdd();

	int GetSceneMaxMRole()
	{
		return m_nMaxMRoleNow;
	}
	int GetSceneIdenti()
	{
		return m_nSceneIdenti;
	}

private:
	void InitMRole(CMRole *pMRole);

};