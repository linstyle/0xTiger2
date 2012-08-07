#pragma once 
#include "CListOfArray.h"

#include <windows.h>


template<typename llist_t, int llist_size, bool bManual=false>
class CLockListOfArray
{
public:
	CListOfArray<llist_t, llist_size, bManual> UserList;
	typedef typename CListOfArray<llist_t, llist_size, bManual>::ELEMENT Element_t;

private:
	CRITICAL_SECTION CriticalSelf;

public:
	CLockListOfArray()
	{
		InitializeCriticalSection(&CriticalSelf);
	}

	~CLockListOfArray()
	{
		DeleteCriticalSection(&CriticalSelf);
	}

	bool Add(const llist_t& e)
	{
		EnterCriticalSection( &CriticalSelf );

		bool b=UserList.Add(e);

		LeaveCriticalSection( &CriticalSelf );

		return b;
	}
	
	llist_t* GetMallocElement()
	{
		EnterCriticalSection( &CriticalSelf );

		llist_t* p=UserList.GetMallocElement();

		LeaveCriticalSection( &CriticalSelf );

		return p;
	}
	
	void Erase(Element_t *p)
	{
		EnterCriticalSection( &CriticalSelf );

		UserList.Erase(p);

		LeaveCriticalSection( &CriticalSelf );
	}

	Element_t* GetListUseHead()
	{
		return UserList.GetListUseHead();
	}
	
	Element_t* GetListFreeHead()
	{
		return UserList.GetListFreeHead();
	}

	Element_t* GetElementAtID(unsigned int nId)
	{
		return UserList.GetElementAtID(nId);
	}
	
	int GetSumElementUse()
	{
		return UserList.GetSumElementUse();
	}

	int GetSumElementFree()
	{
		return UserList.GetSumElementFree();
	}

private:

};