/*
 ���������ˡ�windows ���ı�� 5th���еĴ���
 ���ֶ������𾴣��ؼ�������������ԭ�е����֡�

 ��ʱ���ø��ļ���ֻ���ο�
*/

/******************************************************************************
Module:  CmnHdr.h
Notices: Copyright (c) 2008 Jeffrey Richter & Christophe Nasarre
Purpose: Common header file containing handy macros and definitions
         used throughout all the applications in the book.
         See Appendix A.
******************************************************************************/
#pragma once
#include <windows.h>
#ifdef _X86_
   #define DebugBreak()    _asm { int 3 }
#endif

inline void chMB(PCSTR szMsg) {
   char szTitle[MAX_PATH];
   GetModuleFileNameA(NULL, szTitle, _countof(szTitle));
   MessageBoxA(GetActiveWindow(), szMsg, szTitle, MB_OK);
}

inline void chFAIL(PSTR szMsg) {
   chMB(szMsg);
   DebugBreak();
}

// Put up an assertion failure message box.
inline void chASSERTFAIL(LPCSTR file, int line, PCSTR expr, int errnum) {
   char sz[2*MAX_PATH];
   wsprintfA(sz, "File %s, line %d : %s, errnum:%d", file, line, expr, errnum);
   chFAIL(sz);
}

// Put up a message box if an assertion fails in a debug build.
#ifdef _DEBUG
   #define chASSERT(x) if (!(x)) chASSERTFAIL(__FILE__, __LINE__, #x, GetLastError())
#else
   #define chASSERT(x)
#endif

// Assert in debug builds, but don't remove the code in retail builds.
#ifdef _DEBUG
   #define chVERIFY(x) chASSERT(x)
#else
   #define chVERIFY(x) (x)
#endif