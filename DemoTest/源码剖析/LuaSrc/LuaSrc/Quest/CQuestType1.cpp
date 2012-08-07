#include "CQuestType1.h"

CQuestType1::CQuestType1()
{

}
CQuestType1::~CQuestType1()
{

}

int CQuestType1::GetType1()
{
	return m_nDeriveType;
}

void CQuestType1::SetType1(int nType)
{
	m_nDeriveType = nType;
}