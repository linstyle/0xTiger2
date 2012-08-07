/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                         
    ����˵����  ��ʼ���ȼ�ʱ���Ժ;�̬���
	���£�2012/01/13 
*/

#pragma once
#pragma comment( lib, "USER32" )
#include <windows.h>

#include "CLog2.0.h"

/*
	��л��ѩ�ṩ����,һ����̬�ĺ���
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


#ifdef _X86_
#define DebugBreak()    _asm { int 3 }
#endif

__inline void CmAssert(LPCSTR pFile, int nLine, PCSTR pExpr, int nErrnum)
{
	char szMsg[2*MAX_PATH];
	wsprintfA(szMsg, "File %s, line %d : %s, errnum:%d", pFile, nLine, pExpr, nErrnum);

	char szTitle[MAX_PATH];
	GetModuleFileNameA(NULL, szTitle, _countof(szTitle));
	MessageBoxA(GetActiveWindow(), szMsg, szTitle, MB_OK);
	DebugBreak();
}

/*
	��̬��ʼ��(������������Դ��ʼ������Ե�)ʹ�õ��ж��ꡣ
*/
#define  INITASSERT(a) if ((a)) InitAssert(__FILE__, __LINE__, #a, GetLastError())
__inline void InitAssert(LPCSTR pFile, int nLine, PCSTR pExpr, int nErrnum)
{
	LOGE("Err, InitAssert. Expr:%s, ErrNum:%d\n", pExpr, nErrnum);
	CmAssert(pFile, nLine, pExpr, nErrnum);
}



/*
	��������ʱ���ж��ꡣDEBUG�汾�»ᵯ��+��־��Release��ֻ���¼��־
	MTASSERT����Ϊ������ΪLOG�л��¼__FILE__��Ϣ�����߳�ͻ
*/

#ifdef _DEBUG
	#define  MTASSERT(pFile, nLine, pExpr, nErrnum)	\
	LOGE("Err, MTASSERT. Expr:%s, ErrNum:%d\n", pExpr, nErrnum)	,		\
	CmAssert(pFile, nLine, pExpr, nErrnum)		
#else
	#define  MTASSERT(pFile, nLine, pExpr, nErrnum) \
		LOGE("Err, InitAssert. Expr:%s, ErrNum:%d\n", pExpr, nErrnum),
#endif


#define  IF(a) if( (a) ?(MTASSERT(__FILE__, __LINE__, #a, GetLastError()),1) :  0)

/*
	��MTASSERTһ����ֻ�Ǹ������ʹ�ã������ļ���
	ֻ��IFn����������Ѽ��˵㣬Сn��ʾnet
*/
#ifdef _DEBUG
#define  MTASSERTn(pFile, nLine, pExpr, nErrnum)	\
	LOGNE("Err, MTASSERT. Expr:%s, ErrNum:%d\n", pExpr, nErrnum),		\
	CmAssert(pFile, nLine, pExpr, nErrnum)
#else
#define  MTASSERT(pFile, nLine, pExpr, nErrnum) \
	LOGNE("Err, InitAssert. Expr:%s, ErrNum:%d\n", pExpr, nErrnum),
#endif


#define  IFn(a) if( (a) ?(MTASSERTn(__FILE__, __LINE__, #a, GetLastError()),1) :  0)

/*
	��MTASSERTһ����ֻ�Ǹ��ڴ��(slab)��ʹ�ã������ļ���
	ֻ��IFm����������Ѽ��˵㣬Сn��ʾmemry	
*/
#ifdef _DEBUG
#define  MTASSERTm(pFile, nLine, pExpr, nErrnum)	\
	LOGME("Err, MTASSERT. Expr:%s, ErrNum:%d\n", pExpr, nErrnum)	,		\
	CmAssert(pFile, nLine, pExpr, nErrnum)
#else
#define  MTASSERTm(pFile, nLine, pExpr, nErrnum) \
	LOGME("Err, InitAssert. Expr:%s, ErrNum:%d\n", pExpr, nErrnum),
#endif


#define  IFm(a) if( (a) ?(MTASSERTm(__FILE__, __LINE__, #a, GetLastError()),1) :  0)