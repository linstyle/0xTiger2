#pragma once
//lindp
//2011.7.13

#include "LinuxList.h"

template<class T>
class CListArray
{
public:
	CListArray(int nCount);

private:

public:
	class LIST_ARRAY_NODE
	{
	public:
		T  m_Value;
		struct list_head m_ListNode;
	};

	

private:
	int m_nMaxCount;
	
};