/*
 Moudle:_CScriptLog.h
 Author:lin_style
 Time:	2009/11/18
 Function:��ָ��Ŀ¼��������־�ļ���Ī���Ե�ǰ����Ϊ�ļ���
 Remark:ֻ֧��unicode����
		
*/
#pragma once
#include <windows.h>

#include <stdio.h> 
#include <time.h>
#include <assert.h>


namespace script_log_namespace
{
	const int OUT_PATH_SIZE = 64;
	const int LOG_BUFF_SIZE = 2048;
};

class CScriptLog
{
//variable
public:
	int nOutLevel;
	int nErrCreateFile;
	
	FILE* pOutFileDevice;
	wchar_t strOutPathName[script_log_namespace::OUT_PATH_SIZE];
	wchar_t strOutTemp[script_log_namespace::LOG_BUFF_SIZE];

//function
public:
	CScriptLog();
	CScriptLog(const wchar_t* _pOutPathName);
   ~CScriptLog();

	void WriteLog(int len);

private:
	inline void CreateScriptLog();
	inline void CloseScriptLog();

	wchar_t* GetCurrentTimeLog(wchar_t* pBufferTime);

};

