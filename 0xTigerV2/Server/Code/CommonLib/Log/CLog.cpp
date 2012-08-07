#include "StdAfx.h"
#include "CLog.h"
#include <share.h>

unsigned int WINAPI CLogThread::ProcWrite(void* param)
{
	CLogThread *pLogProcess = (CLogThread*)param;

	while( true==pLogProcess->IsThreadRun() )
	{
		int nCount=pLogProcess->GetLogCount();
		for(int i=0; i<nCount; ++i)
		{
			CLog *pLog = pLogProcess->GetLogAt(i);
			pLogProcess->Flush(pLog);			
		}

		pLogProcess->UpdateFlushTime(); 
		Sleep(name_log::FLUSH_INTERVAL_SECONDS*1000);
	}

	return 0;
}

void CLogThread::Flush(CLog *pLog)
{
	if( false==IsCanFlush() )
	{
		return;
	}

	if( -1==pLog->Flush() )
	{
		wprintf(L"Err, CLogThread::ProcWrite,  Path:%s\n", pLog->GetSavePath());
	}

	pLog->ReCreateSaveTerminal();
}

CLogThread::CLogThread()
{
	m_bThreadRun = true;
	m_idThread = 0;
	m_hThread = NULL;

	UpdateFlushTime(); 
}

CLogThread::~CLogThread()
{
	m_bThreadRun = false;
	EndThread();
}

void CLogThread::InitThread()
{
	m_hThread = (HANDLE)_beginthreadex(NULL, 0, ProcWrite,(void *)this, 0, &m_idThread);
	INITASSERT( 0!=m_hThread );
}

void CLogThread::EndThread()
{
	if( WAIT_FAILED==WaitForSingleObject(m_hThread, 3000) )
	{
		printf("Err, CLog::EndSaveTerminal,ErrNum:%d\n", GetLastError());
	}
	CloseHandle(m_hThread);
}

//void CLogThread::Reg(CLog *pLog)
//{
//	m_LogVt.push_back(pLog);
//}

void CLogThread::Init(CLog *pLog, int nLogCount)
{
	for(int i=0; i<nLogCount; ++i)
	{
		m_LogVt.push_back(&pLog[i]);
	}

	InitThread();
}

bool CLogThread::IsCanFlush()
{
	__time64_t nInterval = CTime::GetSS()- GetFlushTime();

	if( nInterval>=name_log::FLUSH_INTERVAL_SECONDS )
	{
		return true;
	}
	
	return false;
}

void CLogThread::UpdateFlushTime()
{
	m_TimeFlushInterval = CTime::GetSS();
}

__time64_t CLogThread::GetFlushTime()
{
	return m_TimeFlushInterval;
}

bool CLogThread::IsThreadRun()
{
	return true==m_bThreadRun;
}

/*
	CLogPath
*/
void CLogPath::Init(wchar_t *pSaveName, wchar_t *pSavePath)
{
	InitTime();
	InitPath(pSaveName, pSavePath);
}

void CLogPath::InitPath(wchar_t *pSaveName, wchar_t *pSavePath)
{
	int nSaveNameLen = wcslen(pSaveName);
	int nSavePathLen = wcslen(pSavePath);
	memset(m_SavePath, 0, sizeof(m_SavePath));

	assert( (nSaveNameLen+nSavePathLen+name_log::SAVE_NAME_POSTFIX_LEN)
		<(name_log::SAVE_PATH_LEN) );
	
	//������·���ܳ���
	wcsncpy(m_SavePath, pSavePath, nSavePathLen);
	swscanf(pSaveName,  L"%[^.]", m_SavePath+nSavePathLen);

	//�����׺��û��ȡ�ã��������ֳ������¼���
	nSaveNameLen = wcslen(m_SavePath+nSavePathLen);
	
	//��׺ָ������
	m_pSavaNamePostFix = &m_SavePath[nSavePathLen+nSaveNameLen];	

	//�����ƺ�û�пɿ��Ƴ��ȵ�sscanf�汾
	swscanf(pSaveName,  L"%*[^.].%s", m_PostFix);

	UpdatePath();
}

void CLogPath::InitTime()
{
	m_nHour = CTime::GetHH();	
}

bool CLogPath::IsReCreate()
{
	if( CTime::GetHH()!=m_nHour )
	{
		m_nHour = CTime::GetHH();
		return true;
	}

	return false;
}

void CLogPath::UpdatePath()
{
	swprintf(m_pSavaNamePostFix, name_log::SAVE_NAME_POSTFIX_LEN, 
		L"%d.%s", CTime::GetMMDDHH(), m_PostFix);	
}

wchar_t *CLogPath::GetLogPath()
{
	return m_SavePath;
}

CLog::~CLog()
{	
	/*
		��ȻFlush�ӿ���CLogProcess���ƣ��������������ڽ���ʱ��CLog���������д��
		ʣ�����ݡ����ʱ��CLogProcess��fwrite����Ҳ�޹ؽ�Ҫ������ٴ�CLogProcess��
		����CLog��������ʵ���ǲ�ˬ

		�ҵ�ʱд�����Ҫ���ʲô��
	*/
	CloseSaveTerminal();
	delete m_pFlushTempBuffer;
}

void CLog::Init(wchar_t *pSaveName, wchar_t *pSavePath)
{
	m_nSumWriteByte = 0;

	m_LogPath.Init(pSaveName, pSavePath);
	InitSaveBuffer();
	CreateSaveTerminal();
}

void CLog::TracerMe()
{

}
#define CLOG_WRITE_LEN_ERR if( (name_log::LINE_BUFFER_LEN-nSumLen)<=0 )		\
{																															\
printf("Warning, CLog::Write:(LINE_BUFFER_LEN(%d)-nSumLen(%d))<=0\n",	\
	   name_log::LINE_BUFFER_LEN,  nSumLen);													\
	   return -1;																										\
}																														    \

int CLog::Write(LOG_LEVEL Level, wchar_t* format, va_list VaList)
{
	int nLen=0, nSumLen=0;
	wchar_t LineBuffer[name_log::LINE_BUFFER_LEN];
	wchar_t *pLineBuffer=LineBuffer;

	//WriteTime;
	TIMEW_HHMMSS TimeHHMMSS;
	CTime::GetWHHMMSS(&TimeHHMMSS);
	nLen = swprintf(pLineBuffer, name_log::LINE_BUFFER_LEN-nSumLen, L"%s ", TimeHHMMSS.m_Buffer);
	nSumLen += nLen;
	pLineBuffer += nLen;
	CLOG_WRITE_LEN_ERR

	//WriteDetail
	if( (Level&0xffff0000) & name_log::PUT_MASK_DETAIL )
	{
		nLen = swprintf(pLineBuffer, name_log::LINE_BUFFER_LEN-nSumLen, L"[Function]:%s, [Line]:%d\n", __WFUNCTION__, __LINE__);
	}
	nSumLen +=nLen;
	pLineBuffer += nLen;
	CLOG_WRITE_LEN_ERR

	//WriteContent
	//va_list valist;
	//va_start(valist, format);
	nLen = vswprintf(pLineBuffer, name_log::LINE_BUFFER_LEN-nSumLen, format, VaList);
	//va_end(valist);
	nSumLen += nLen;
	pLineBuffer += nLen;

	//wchar_t,����char��С��2
	nSumLen *= 2;

	//WriteTerminal
	if( (Level&0xffff0000) & name_log::PUT_MASK_CONSOLE )
	{
		wprintf(L"%s\n", LineBuffer);
	}

	if( (Level&0xffff0000) & name_log::PUT_MASK_HD )
	{
		if ( -1==m_CircleBuffer.WriteBuffer((char*)LineBuffer, nSumLen) )
		{
			printf("Warning, CLog::Write:m_CircleBuffer.WriteBuffer, nSumLen(%d)\n", nSumLen);
		}
		return -1;
	}

	m_nSumWriteByte += nSumLen;
	return  0;
}

void CLog::InitSaveBuffer()
{
	m_pFlushTempBuffer = new char[name_log::CIRCLE_BUFFER_LEN];	
	m_CircleBuffer.Init(name_log::CIRCLE_BUFFER_LEN);
}

void CLog::CreateSaveTerminal()
{
	int nResult;
	m_pSavaPath = m_LogPath.GetLogPath();
	//nResult = _wfopen_s(&m_fPutDevice, m_pSavaPath, L"a,ccs=UTF-8"); 
	m_fPutDevice = _wfsopen(m_pSavaPath,  L"a,ccs=UTF-8", _SH_DENYWR);
	if( NULL == m_fPutDevice )
	{
		printf("Err, CLog::CreateSaveTerminal:ErrID(%d)\n", GetLastError());
		assert(0);
	}
}

void CLog::CloseSaveTerminal()
{
	if(NULL!=m_fPutDevice)
	{
		fclose(m_fPutDevice);
	}
}

unsigned long CLog::SizeSaveTerminal()
{
	
	return 0;
}

wchar_t* CLog::GetSavePath()
{
	return m_pSavaPath;
}

int CLog::Flush()
{
	//int nWriteLen = m_CircleBuffer.GetUseLength();

	//if(nWriteLen==0)
	//{
	//	return 0;
	//}

	//if( -1==m_CircleBuffer.ReadBuffer(m_pFlushTempBuffer, nWriteLen) )
	//{
	//	printf("Err, CLog::Flush():ReadBuffer\n");
	//	return -1;
	//}

	//if( 0==fwrite(m_pFlushTempBuffer, 1, nWriteLen, m_fPutDevice) )
	//{
	//	printf("Err, CLog::Flush():fwrite:ErrNum(%d)\n", GetLastError());
	//	return -1;
	//}
	return 0;
}

void CLog::ReCreateSaveTerminal()
{
	if( true==m_LogPath.IsReCreate() )
	{
		m_LogPath.UpdatePath();
		CloseSaveTerminal();
		CreateSaveTerminal();
	}
}