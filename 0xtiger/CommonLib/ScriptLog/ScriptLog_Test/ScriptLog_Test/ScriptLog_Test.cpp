// ScriptLog_Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vld.h>
#include "CScriptLog.h"

__time64_t TestGetCurrentTimeLog()
{
	__time64_t long_time;
	
	_time64( &long_time );           

	return long_time;
}

int _tmain(int argc, _TCHAR* argv[])
{
	/*
	for(int i=1; i<5; ++i)
	{
		LTRACE(i, L"zzzÎÒ222ºÍ111Äãddd:%d\n", i);		
	}
	*/

	wchar_t buff[128];
	for(int i=0; i<100; ++i)
	{
		int j = GetTickCount();
		cout<<j<<endl;
	}


	return 0;
}

