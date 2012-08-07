#pragma once
#include "CQuestObject.h"
/*
	任务类型2
*/

class CQuestType1:public CQuestObjectBase
{
public:
	CQuestType1();
	~CQuestType1();

	int GetType1();
	void SetType1(int nType);
private:

public:

private:
	int m_nDeriveType;

};