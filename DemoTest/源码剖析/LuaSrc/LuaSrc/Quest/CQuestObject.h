#pragma once

/*
	������Ҫ�Ļ������ݽṹ
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