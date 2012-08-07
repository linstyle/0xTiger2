/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2011/2/21                                                       
    ����˵����  һ���ֵȼ���LEVEL��ͨ��ָ��LEVEL�Ĳ�ͬ��
					   ���ݻ�д����ͬ���ļ�����Ƕ�CLOG��һ����װ����
*/
#pragma once

#include "Singleton.h"
#include "CLog.h"


//���ⲿֱ�ӵ��õĽӿ�
void LOG(LOG_LEVEL Level, wchar_t* format, ...);

class CLogManager:public Singleton<CLogManager>
{
public:
	CLogManager();
	~CLogManager();

	void Init();
	void Write(LOG_LEVEL Level, wchar_t* format, va_list VaList);
private:

public:

private:
	CLog *m_pLog;
	CLogThread m_LogThread;
};

#define g_LogManager CLogManager::getSingleton()