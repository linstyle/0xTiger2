/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/09/18                                                         
    ����˵����  �����߳�+һ��˫������
				������ʽ: xxxʱ��(xxx��ʾ�û�������ַ�)
*/

#pragma once
#include <windows.h>
#include <process.h>
#include <stdio.h> 
#include <vector>


#include "MTASSERT.h"
#include "CCircleBuffer.h"
#include "CTime.h"

#define __WFILE__2(x) L ## x
#define __WFILE__1(x) __WFILE__2(x)
#define __WFILE__ __WFILE__1(__FILE__)

#define __WFUNCTION__2(x) L ## x
#define __WFUNCTION__1(x) __WFUNCTION__2(x)
#define __WFUNCTION__ __WFUNCTION__1(__FUNCTION__)

#define __WLINE__2(x) L ## x
#define __WLINE__1(x) __WLINE__2(x)
#define __WLINE__ __WLINE__1(__LINE__)

namespace name_log
{
	const int FLUSH_INTERVAL_SECONDS = 1;				//д�������ն˵ļ������

	const int CREATE_SAVE_SIZE = 10*1024*1024;			//mb,���ļ�����ʱ�����½����ļ�
	const int SAVE_PATH_LEN = 128;							   //·�����ȣ�·��+�ļ���
	const int SAVE_NAME_POSTFIX_LEN = 16;				       //������ļ�����ʱ��ĳ���+��׺

	const int LINE_BUFFER_LEN = 32*1024;					   //kb,��������д����ʱ�������Ĵ�С
	const int CIRCLE_BUFFER_LEN = 5*1024*1024;			//mb,���λ�������С,д�뵽�ն�ǰ����ʱ��ſռ�
	/*
		����ն˵Ŀ���
		32λ��bit,��16λ��ʾ����նˡ������ϸ�ȿ��ƣ�
				  ��16λ��ʾ��Ϣ�ȼ�
		�ж��﷨: if( PUT_MASK_XX & PUT_MASK )
				  {
						�����XX�ն�
				  }
	*/
	const int PUT_MASK_CONSOLE = 0x10000;		//����̨
	const int PUT_MASK_HD       =     0x100000;		//����
	const int PUT_MASK_DETAIL =   0x1000000;		//�Ƿ���ϸ

	const int PUT_MASK = PUT_MASK_HD|PUT_MASK_DETAIL;
};

/*
	����ȼ�
*/
enum LOG_LEVEL
{
	//ȷ��|���˳�����﹩CLOGLEVEL��Ϊ������ʼ��
	LOG_NOTIC = name_log::PUT_MASK|0,			//��ͨ���
	LOG_WARN =  name_log::PUT_MASK|1,		//����
	LOG_ERROR = name_log::PUT_MASK|2	,		//����
	LOG_MAX														//&0xffff0000
};

class CLog;

class CLogThread
{
public:
	CLogThread();
	~CLogThread();

	void Init(CLog *pLog, int nLogCount);
	//void Reg(CLog *pLog);
	void Flush(CLog *pLog);
	void UpdateFlushTime();

private:
	static unsigned int WINAPI ProcWrite(void* param);

	bool IsThreadRun();
	void InitThread();
	void EndThread();

	bool IsCanFlush();
	
	__time64_t GetFlushTime();
	
	int GetLogCount()
	{
		return m_LogVt.size();
	}

	CLog* GetLogAt(int i)
	{
		return m_LogVt[i];
	}

public:

private:
	bool m_bThreadRun;
	HANDLE m_hThread;
	unsigned int m_idThread;

	std::vector<CLog*> m_LogVt;
	__time64_t m_TimeFlushInterval;
};

/*
	������־�ļ����ı仯
*/
class CLogPath
{
public:
	void Init(wchar_t *pSaveName, wchar_t *pSavePath);

	bool IsReCreate();
	//ˢ����·����
	void UpdatePath();
	wchar_t * GetLogPath();
private:
	void InitPath(wchar_t *pSaveName, wchar_t *pSavePath);
	void InitTime();

public:

private:
	wchar_t *m_pSavaNamePostFix;										//��׺ָ�룬����ʱ��+��׺
	wchar_t   m_PostFix[8];													//��׺��
	wchar_t   m_SavePath[name_log::SAVE_PATH_LEN];		//����·��

	int m_nHour;		//�ϻص�ʱ��,Сʱ
};

class CLog
{
public:
	~CLog();
	void Init(wchar_t *pSaveName, wchar_t *pSavePath=L"");
	void TracerMe();
	
	/*
		����Ա䳤�������ж�η�װ����ô����Ӧ��д��va_list���ͽ��д���
		ͬʱ��˭�����ı䳤������˭���ͷ�
	*/
	int Write(LOG_LEVEL Level, wchar_t* format, va_list VaList);
	int Flush();
	
	void ReCreateSaveTerminal();
	unsigned long SizeSaveTerminal();

	wchar_t* GetSavePath();

private:
	void CreateSaveTerminal();
	void CloseSaveTerminal();
	void InitSaveBuffer();

public:

private:
	//·���Ĺ���
	CLogPath m_LogPath;

	//������
	CCircleBuffer m_CircleBuffer;
	//��flushʱ����m_CircleBuffer�п�����������ʱ��
	char *m_pFlushTempBuffer;	

	//����ն˾��
	FILE* m_fPutDevice;

	//����·��
	wchar_t* m_pSavaPath;

	//tracer
	__int64  m_nSumWriteByte;
}; 

