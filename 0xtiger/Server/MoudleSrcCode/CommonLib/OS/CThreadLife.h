#pragma once

#include <Winsock2.h>
#include <Windows.h>
#include <process.h>

#include "../0x_Exception.h"
/*
	��Ա���ܣ�һ���߳������ڵļ򵥷�װ.
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