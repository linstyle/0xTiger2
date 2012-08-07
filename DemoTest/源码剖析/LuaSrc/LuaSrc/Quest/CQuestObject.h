#pragma once

/*
	任务需要的基础数据结构
*/
class CQuestObjectBase
{
public:
	CQuestObjectBase();
	~CQuestObjectBase();

	int GetType();
	void SetType(int nType);	
private:
	
public:


private:
	int m_nType;
};