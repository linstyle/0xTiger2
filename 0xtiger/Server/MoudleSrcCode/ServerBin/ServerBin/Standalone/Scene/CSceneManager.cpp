#include "CSceneManager.h"
#include "../../CConfigManager.h"

void CSceneManager::TracerMe()
{
	printf("\nCSceneManager::TracerMe\n");
	printf("nSceneMaxCount:%d\n", nSceneMaxCount);
	for(int i=0; i<nSceneMaxCount; ++i)
	{
		m_pScene[i].CallBackTracerMe();
		printf("\n");
	}
}

CSceneManager::CSceneManager()
{
	ReadFromConfigManager();
	TracerMe();
}

CSceneManager::~CSceneManager()
{
	delete []m_pScene;
}

void CSceneManager::ReadFromConfigManager()
{
	CConfigManager::ReadSceneCount(&nSceneMaxCount);
	m_pScene = new CScene[nSceneMaxCount];

	int nMaxMRole, nIdenti;
	for(int i=0; i<nSceneMaxCount; ++i)
	{
		CConfigManager::ReadSceneSelfInfo(i, &nIdenti);
		m_pScene[i].Init(nIdenti);
	}

}