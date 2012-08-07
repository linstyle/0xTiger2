/*
 Moudle:CScriptLog.h
 Author:lin_style
 Time:	2009/11/18
 Function:��ָ��Ŀ¼��������־�ļ���Ī���Ե�ǰ����Ϊ�ļ���
 Remark:�ṩ���������ļ�
		ֻ֧��unicode����		
*/

//�Ƿ����ļ�������������������д����Ϣ
#define SCRIPT_LOG_DETAIL

#define __WFILE__2(x) L ## x
#define __WFILE__1(x) __WFILE__2(x)
#define __WFILE__ __WFILE__1(__FILE__)

#define __WFUNCTION__2(x) L ## x
#define __WFUNCTION__1(x) __WFUNCTION__2(x)
#define __WFUNCTION__ __WFUNCTION__1(__FUNCTION__)

#define __WLINE__2(x) L ## x
#define __WLINE__1(x) __WLINE__2(x)
#define __WLINE__ __WLINE__1(__LINE__)


#ifdef SCRIPT_LOG_DETAIL
#define SCRIPTLOG_TRACE_DETAIL(level) scriptlog_trace(level, L"<File>:%s\n<Function>:%s\n<Line>:%d\n", __WFILE__, __WFUNCTION__, __LINE__)
#else
#define SCRIPTLOG_TRACE_DETAIL 
#endif

#define LTRACE(level, format, ...) \
	SCRIPTLOG_TRACE_DETAIL(level); \
	scriptlog_trace(level, format##L"\n",  __VA_ARGS__);


extern "C" void scriptlog_set_level(int level);
extern "C" int scriptlog_get_errno();
extern "C" void scriptlog_trace(int level, wchar_t* format, ...);