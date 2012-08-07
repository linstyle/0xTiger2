#include "CQuestObject.h"
CQuestObjectBase::CQuestObjectBase()
{
	m_nType = 100;
}

CQuestObjectBase::~CQuestObjectBase()
{

}


int CQuestObjectBase::GetType()
{
	return m_nType;
}

void CQuestObjectBase::SetType(int nType)
{
	m_nType = nType;
}