#pragma once

#include <list>
#include <windows.h>
#include <algorithm>
using namespace std;

/*
	由于STL不是一个有虚析构函数的物件，所以CLockList的对象，禁止用delete list(基类)。这样会使得派生类的析构无法调用
	所以，这里把STL做为一个对象.
	并且爷也按stl.list的命名规格重载了部分函数
*/
template<class _Ty>
class CLockList
{
public:
	list<_Ty> UserList;

private:
	
	CRITICAL_SECTION CriticalSelf;

public:
	CLockList()
	{
		InitializeCriticalSection(&CriticalSelf);
	}

	~CLockList()
	{
		DeleteCriticalSection(&CriticalSelf);
	}

	int size() const
	{
		return UserList.size();	
	}

	void push_back(const _Ty& _Val)
	{
		UserList.push_back(_Val);
	}

	void safe_push_back(const _Ty& _Val)
	{
		EnterCriticalSection( &CriticalSelf );

		UserList.push_back(_Val);

		LeaveCriticalSection( &CriticalSelf );
	}

	void safe_erase(_Ty _Where)
	{
		EnterCriticalSection( &CriticalSelf );
		
		list<_Ty>::iterator pos;

		pos = find(UserList.begin(), UserList.end(), _Where);
		UserList.erase(pos);

		LeaveCriticalSection( &CriticalSelf );	
	}


	

private:
};