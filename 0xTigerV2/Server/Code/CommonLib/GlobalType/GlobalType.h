/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/17                                                         
    ����˵����  ���õ����͡�ƽ̨�ؼ��ֶδ�С����
*/
#pragma once

#include <stdio.h>
#include <winsock2.h>
#include <windows.h>
#include "MTASSERT.h"
#include "CLog2.0.h"
#include "CMyStackWalker.h"


typedef unsigned __int64 MGUID;

typedef signed __int64 S64;
typedef signed __int32 S32;
typedef signed __int16 S16;
typedef signed __int8 S8;

typedef unsigned __int64 U64;
typedef unsigned __int32 U32;
typedef unsigned __int16 U16;
typedef unsigned __int8 U8;


#define _ALIGN(a,size) (((a)+(size)-1)&(~((size)-1)))
const unsigned int  __PAGE_SIZE_BYTE = 4096;		 //byte
const unsigned int __ALIGN_SIZE_LONG = sizeof(long);		 //4�ֽڶ���,long�ڴ����ƽ̨�º�CPUλ�����
const unsigned int __ALIGN_SIZE_PAGE = __ALIGN_SIZE_LONG;     //���Ӧ����API�õ��ɣ�

#define printu(level) printf(level##",%s::%s:%d, %d\n", __FILE__, __FUNCTION__, __LINE__, GetLastError())

#define DELAY_CONTINUE(time) for(static DWORD dwOld = GetTickCount(); (GetTickCount()-dwOld)>=time; dwOld = GetTickCount() )

#define FREE_NULL(p)	\
do									\
{										\
	__try								\
	{									\
		if(p)							\
			free(p);					\
		p=NULL;					\
	}									\
	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))		\
	{										\
		return;							\
	}										\
} while (0)



#define DELETE_NULL(p)	\
do										\
{											\
	__try									\
	{										\
		if(p)								\
			delete p;					\
		p=NULL;						\
	}										\
	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))		\
	{										\
		return;							\
	}										\
} while (0)


#define DELETE_ARRAY_NULL(p)	\
do										\
{											\
	__try									\
	{										\
		if(p)								\
			delete []p;				\
		p=NULL;						\
	}										\
	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))		\
	{										\
		return;							\
	}										\
} while (0)