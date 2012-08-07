#include "..\StdAfx.h"
#include "CThread.h"

CThread::CThread()
{
	m_dwStartTime = 0;
}

CThread::~CThread()
{
	CloseHandle(m_hThread);
}