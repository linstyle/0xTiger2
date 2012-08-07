#include "StdAfx.h"
#include "CLock.h"

CLock::CLock()
{
	InitializeCriticalSection(&cs);
}

CLock::~CLock()
{
	DeleteCriticalSection(&cs);
}



CFastLock::CFastLock():m_lLock(FASTLOCK_UNLOCK)
{
	
}


/* ʹ�÷���

CFastLock g_FastLock;

g_FastLock.Lock();

g_FastLock.UnLock();

*/