/*  
	��    �ߣ��ֶ�ƽ                                                              
	����ʱ�䣺2012/1/5 
    ����˵������־��������
*/
/*
���װ


�����߳�->���λ���->д��
д������-���λ���


�ļ���->����ǰ�ȶ�->�ҵ����ʵ�������û�У��½�

���ʵ��->д��ӿ�
        ->�ж��ļ��ؽ�����

�ر��ļ�-�����ļ�
*/
#pragma once
#include <wchar.h>
#include <map>
#include <string>

#include "CTime.h"
#include "CCircleBuffer.h"
#include "Singleton.h"
using namespace std;

class CLogManager2;
/*
	�Զ����LOG��

	Ĭ�ϵ���LOGN/W/E(
	Notic,��ͨ��Ϣ;
	Warning,������Ϣ;
	Err, ������Ϣ

	1)��չ�º갴��LOGXXX����.
    2)�����ͳһ��void CLogManager2::Init()���������
	3)ֻ֧��һ��Ŀ¼����
*/
#define g_Log2 CLogManager2::getSingleton()

//ҵ���߼�
#define  LOGN(format, ...)  g_Log2.Write("log\\Notice", __FILE__, __LINE__, format, __VA_ARGS__)
#define  LOGW(format, ...)  g_Log2.Write("log\\Warning", __FILE__, __LINE__, format, __VA_ARGS__)
#define  LOGE(format, ...)  g_Log2.Write("log\\Err", __FILE__, __LINE__, format, __VA_ARGS__)

//����ģ��
#define  LOGNE(format, ...)  g_Log2.Write("log\\ErrNet", __FILE__, __LINE__, format, __VA_ARGS__)
#define  LOGNN(format, ...)  g_Log2.Write("log\\NoticeNet", __FILE__, __LINE__, format, __VA_ARGS__)

//�ڴ�ģ��
#define  LOGME(format, ...)  g_Log2.Write("log\\ErrMemery", __FILE__, __LINE__, format, __VA_ARGS__)
#define  LOGMN(format, ...)  g_Log2.Write("log\\NoticeMemery", __FILE__, __LINE__, format, __VA_ARGS__)


#define  LOGU1(format, ...) g_Log2.Write("log\\UserDefine1", __FILE__, __LINE__, format, __VA_ARGS__)



namespace name_log2
{
	const int SAVE_FILE_TITLE_NAME_LEN = 32;   //������ļ�������(������ʱ��)
	const int SAVE_FILE_NAME_LEN = SAVE_FILE_TITLE_NAME_LEN+30;   //�ܳ��ȣ�30Ϊʱ��+.log

	const int LINE_BUFFER_LEN = 32*1024;        //kb,��������д����ʱ�������Ĵ�С
//#todo �����ܲ����Ż��ɶ����־ʹ��һ������
	//���λ�������С,д�뵽�ն�ǰ����ʱ��ſռ�, Ҫ����LINE_BUFFER_LEN
	const int CIRCLE_BUFFER_LEN = LINE_BUFFER_LEN*3;  

	/*
		����ն˵Ŀ���
	*/
	const int PUT_MASK_CONSOLE = 0x1;		//����̨
	const int PUT_MASK_HD = 0x10;			//����

	const int PUT_MASK = PUT_MASK_CONSOLE|PUT_MASK_HD;
};


class CLog2
{
public:
	CLog2();
	~CLog2();

	bool Init(const char* pSaveFileName);
	void Write(LPCSTR pFile, int nLine, LPCSTR format, va_list VaList);
	void FlushWrite();

private:
	void InitCircleBuffer();
	void Release();

	//�ؽ������ն�
	void ReCreateSaveTerminal();
	//�����ն�
	bool CreateSaveTerminal();
	//�ر�
	void CloseSaveTerminal();

	//����������ն�
	void WriteTerminal(LPCSTR pFile, int nLine, const char* format, va_list VaList);

public:

private:
	//�ն˾��������ֻ��Ӳ�̣�
	FILE* m_hFile;

	/*
		������
	*/
	//����д��
	char m_szLineBuffer[name_log2::LINE_BUFFER_LEN];  

	//���λ���
	CCircleBuffer m_CircleBuffer;

	//�ļ���
	char m_szFileTitleName[name_log2::SAVE_FILE_TITLE_NAME_LEN];
	char m_szFileName[name_log2::SAVE_FILE_NAME_LEN ];

	//ʱ��
	DWORD m_nFileNameHour;
};


class CLogManager2:public Singleton<CLogManager2>
{
public:
	CLogManager2();
	~CLogManager2();

	void Write(const char* pFileName,  LPCSTR pFile, int nLine, LPCSTR format, ...);

private:
	void Init();
	void StartThread();

	void Release();
	void StopThread();

	CLog2* FindLogInstance(const char* pFileName);
	CLog2* NewLogInstantce(const char* pFileName);

	static unsigned int WINAPI ThreadWrite(void* param);
public:

private:
	typedef std::map<std::string,CLog2*> MAP_LOG_INSTANCE;
	MAP_LOG_INSTANCE m_mapLogInstantce;

	volatile bool m_bThreadRun;
	HANDLE m_hThread;
	unsigned int m_idThread;
};










