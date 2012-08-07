#include "_CScriptLog.h"

namespace script_log_instance_namespace
{
	CScriptLog g_ScriptLog;
};

extern "C" void scriptlog_set_level(int level)
{
	script_log_instance_namespace::g_ScriptLog.nOutLevel = level;
}

extern "C" int scriptlog_get_errno()
{
	return script_log_instance_namespace::g_ScriptLog.nErrCreateFile;
}

extern "C" void scriptlog_trace(int level, wchar_t* format, ...)
{
	CScriptLog *pScriptLog = &script_log_instance_namespace::g_ScriptLog;
	if(level>script_log_instance_namespace::g_ScriptLog.nOutLevel)
	{
		va_list valist;
		va_start(valist, format);

		int len;
		len = vswprintf(pScriptLog->strOutTemp, script_log_namespace::LOG_BUFF_SIZE-8, format, valist);
		va_end(valist);
				
		::OutputDebugString(pScriptLog->strOutTemp); 
		pScriptLog->WriteLog(len);	
	}
}


CScriptLog::CScriptLog()
{
	pOutFileDevice = NULL;
	nOutLevel = 0;
	nErrCreateFile = 0;

	wchar_t BufferTime[script_log_namespace::OUT_PATH_SIZE/2];
	wcsncpy(strOutPathName, GetCurrentTimeLog(BufferTime), script_log_namespace::OUT_PATH_SIZE/2);

	CreateScriptLog();
}

CScriptLog::CScriptLog(const wchar_t* _pOutPathName)
{
	pOutFileDevice = NULL;
	nOutLevel = 0;
	nErrCreateFile = 0;

	wcsncpy(strOutPathName, _pOutPathName, script_log_namespace::OUT_PATH_SIZE-8);

	CreateScriptLog();
}

CScriptLog::~CScriptLog()
{
	CloseScriptLog();
}

void CScriptLog::CreateScriptLog()
{
	nErrCreateFile = _wfopen_s(&pOutFileDevice, strOutPathName, L"a,ccs=UTF-8");	
}

void CScriptLog::CloseScriptLog()
{
	if( pOutFileDevice )
	{
		fclose(pOutFileDevice);
	}	
}

void CScriptLog::WriteLog(int len)
{
	//vswprintf居然在空间不够时回返回-1
	if( len>>31 )
	{
		return;
	}
	assert(pOutFileDevice);

	fwrite(strOutTemp, len, 2, pOutFileDevice);
	fflush(pOutFileDevice);
}

wchar_t* CScriptLog::GetCurrentTimeLog(wchar_t* pBufferTime)
{
	struct tm  TimeLocal;
	__time64_t long_time;
	
	_time64( &long_time );           

	_localtime64_s(&TimeLocal, &long_time ); 	

	_snwprintf(pBufferTime, 
			   script_log_namespace::OUT_PATH_SIZE/2-8, L"%d%d%d.txt", 
			   TimeLocal.tm_year+1900, TimeLocal.tm_mon+1, TimeLocal.tm_mday);

	return pBufferTime;
}