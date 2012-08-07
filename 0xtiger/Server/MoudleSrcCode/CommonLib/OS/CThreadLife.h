#pragma once

#include <Winsock2.h>
#include <Windows.h>
#include <process.h>

#include "../0x_Exception.h"
/*
	针对本框架，一个线程生命期的简单封装.
*/

class CThreadLife
{
public:
	HANDLE hThreadSelf;
	unsigned int idThreadSelf;

private:

public:
	~CThreadLife();

	bool Init();
	void virtual Start(void *pArguments) = 0;
	DWORD End();

private:
};