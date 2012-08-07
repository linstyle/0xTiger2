#include "CThreadLife.h"



bool CThreadLife::Init()
{

	return true;
}

DWORD CThreadLife::End()
{
	//
	//等待n秒后返回，需要判断是否超时
	return WaitForMultipleObjects(1, &hThreadSelf, true, 2000);
}

CThreadLife::~CThreadLife()
{
	CloseHandle(hThreadSelf);
}