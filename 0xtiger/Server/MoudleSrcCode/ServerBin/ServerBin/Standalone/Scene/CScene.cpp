#include "CScene.h"


void CScene::CallBackTracerMe()
{
	printf("\nCScene::CallBackTracerMe\n");
	printf("SceneIdenti:%d	m_nMaxMRoleNow:%d\n", m_nSceneIdenti, m_nMaxMRoleNow);
	MRoleManager.CallBackTracerMe();
}

void CScene::Init(int nSceneIdenti)
{
	m_nSceneIdenti = nSceneIdenti;	
}


void CScene::CallBackDoing()
{
	printf("\nCScene::CallBackDoing()\n");
	printf("Indenti:%d\n", m_nSceneIdenti);
}

CMRole* CScene::MRoleAdd()
{
	CMRole *p = MRoleManager.MRoleAdd();
	if( NULL==p ) 
	{
		printf("Warning, CMRoleManager::MRoleAdd(), NULL==p\n");
		return NULL;
	}

	InitMRole(p);
	return p;
}

/*
	private
*/

void CScene::InitMRole(CMRole *pMRole)
{
	pMRole->MRoleHead.InScene.nWhereIdenti = GetSceneIdenti();
}