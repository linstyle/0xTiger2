#include "StdAfx.h"
#include "CLogManager.h"

initialiseSingleton(CLogManager);

void LOG(LOG_LEVEL Level, wchar_t* format, ...)
{
	va_list valist;
	va_start(valist, format);
	g_LogManager.Write(Level, format, valist);
	va_end(valist);
}

CLogManager::CLogManager()
{
	Init();
}

CLogManager::~CLogManager()
{
	delete []m_pLog;
}

void CLogManager::Init()
{
	int nLogCount = LOG_MAX & 0xffff;
	m_pLog = new CLog[nLogCount];

	/*
		������ݳ�ʼ���Ķ�����д��·�����ȵ�.��Level��ʾ��ö�ٶ�Ӧ
		���Ҫע�����кŲ�Ҫ�����±�
	*/
	m_pLog[0].Init(L"Notic.log");
	m_pLog[1].Init(L"WARN.log");
	m_pLog[2].Init(L"ERROR.log");

	m_LogThread.Init(m_pLog, 3);
}


void CLogManager::Write(LOG_LEVEL Level, wchar_t* format, va_list VaList)
{
	int nLogIndex = Level & 0xffff;
	assert( nLogIndex<(LOG_MAX & 0xffff) );

	m_pLog[nLogIndex].Write(Level, format, VaList);
}