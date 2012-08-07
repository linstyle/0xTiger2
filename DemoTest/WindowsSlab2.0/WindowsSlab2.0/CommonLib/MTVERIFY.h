/*
 * MtVerify.h
 *
 * Error handling for applications in
 * "Multitheading Applications in Win32"
 *
 * The function PrintError() is marked as __inline so that it can be
 * included from one or more C or C++ files without multiple definition
 * errors. For the examples in this book, this works fine.
 * To use the PrintError() in an application, it should be taken out,
 * placed in its own source file, and the "__inline" declaration removed
 * so the function will be globally available.
 */

/*  作者：		林东平                                                              
	创建时间：	2010/06/21                                                         
    功能说明：  初始化等即时调试和静态检测
*/

/*
 这里引用了《windows多线程编程》中的代码
 保持对作者尊敬，关键代码名都采用原有的名字。 

 对于一些调试记录，采取以下三种
 1.debug版中的assert
 2.一些初始化以及需要及时调试的，本文件中的MTVERIFY
 3.一些信息记录，LOG文件
*/
#pragma once
#pragma comment( lib, "USER32" )
#include <windows.h>
#include <crtdbg.h>
#include <stdlib.h>
#define MTASSERT(a) _ASSERTE(a)


#define MTVERIFY(a) if (!(a)) PrintError(#a,__FILE__,__LINE__,GetLastError())

__inline void PrintError(LPSTR linedesc, LPSTR filename, int lineno, DWORD errnum)
{
	LPSTR lpBuffer;
	char errbuf[256*2];
#ifdef _WINDOWS
	char modulename[MAX_PATH];
#else // _WINDOWS
	DWORD numread;
#endif // _WINDOWS

	FormatMessageA( FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		errnum,
		LANG_NEUTRAL,
		(LPSTR)&lpBuffer,
		0,
		NULL );

	wsprintfA(errbuf, "\nThe following call failed at line %d in %s:\n\n"
               "    %s\n\nReason: %s\n", lineno, filename, linedesc, lpBuffer);

#ifndef _WINDOWS
	WriteFile(GetStdHandle(STD_ERROR_HANDLE), errbuf, strlen(errbuf), &numread, FALSE );	
#else
	GetModuleFileName(NULL, modulename, MAX_PATH);
	MessageBox(NULL, errbuf, modulename, MB_ICONWARNING|MB_OK|MB_TASKMODAL|MB_SETFOREGROUND);
#endif
	system("pause");
	exit(EXIT_FAILURE);
}


/*
	感谢飞雪提供代码
*/
#ifdef	HAS_STATIC_ASSERT
	#define	STATIC_ASSERT(x) static_assert(x, #x)
#else
	namespace
	{
		template <bool x>
			struct STATIC_ASSERTION_FAILURE;
		template <>
			struct STATIC_ASSERTION_FAILURE<true> { enum { value = 1 }; };
		template<int x>
			struct static_assert_test{};
	}
	#define STATIC_ASSERT(x) typedef static_assert_test<\
									sizeof(STATIC_ASSERTION_FAILURE<(bool)(x) >)\
									>	static_assert_typedef
#endif