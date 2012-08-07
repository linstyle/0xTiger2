#pragma once
#include "CQuestObject.h"
/*
	任务类型2
*/

class CQuestType2:public CQuestObjectBase
{
public:
	CQuestType2();
	~CQuestType2();

	int GetType2();
	void SetType2(int nType);
private:

public:

private:
	int m_nDeriveType;

};