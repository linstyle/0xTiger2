/*
 Moudle:CScriptLog.h
 Author:lin_style
 Time:	2009/11/18
 Function:在指定目录下生成日志文件，莫非以当前日期为文件名
 Remark:提供对外申明文件
		只支持unicode编码		
*/

//是否开启文件名、函数名、行数等写入信息
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