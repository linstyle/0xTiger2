#pragma once

#include <stdio.h>

#include "CScene.h"

class CSceneManager
{
public:
	

private:
	CScene *m_pScene;	
	int nSceneMaxCount;

public:
	CSceneManager();
	~CSceneManager();

	CScene* GetScene(int nIndex)
	{
		return &m_pScene[nIndex];
	}
	int GetCount()
	{
		return nSceneMaxCount;
	}

private:
	void TracerMe();
	void ReadFromConfigManager();
};