#include "CThreadLife.h"



bool CThreadLife::Init()
{

	return true;
}

DWORD CThreadLife::End()
{
	//
	//�ȴ�n��󷵻أ���Ҫ�ж��Ƿ�ʱ
	return WaitForMultipleObjects(1, &hThreadSelf, true, 2000);
}

CThreadLife::~CThreadLife()
{
	CloseHandle(hThreadSelf);
}