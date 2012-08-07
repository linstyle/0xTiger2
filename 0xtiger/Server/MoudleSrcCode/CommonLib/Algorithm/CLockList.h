#pragma once

#include <list>
#include <windows.h>
#include <algorithm>
using namespace std;

/*
	����STL����һ�������������������������CLockList�Ķ��󣬽�ֹ��delete list(����)��������ʹ��������������޷�����
	���ԣ������STL��Ϊһ������.
	����үҲ��stl.list��������������˲��ֺ���
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