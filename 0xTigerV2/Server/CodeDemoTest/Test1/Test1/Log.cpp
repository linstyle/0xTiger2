// Template.cpp : Defines the entry point for the console application.
//
/*
	日志，异常，一起搁这了
*/
//
#include "stdafx.h"
//#include <vld.h>
//#include "CCommonLibInit.h"
//#include "MTASSERT.h"
//#include "StackWalker.h"
//
//bool volatile g_bQuit;
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	new CCommonLibInit;
//	//CLogManager2 LogManager2;
//
//	LOGN("林东平 Notice:%d\n",1);
//	LOGW("林东平 Warning:%d\n",2);
//	LOGE("林东平 Err:%d\n",3);
//	LOGU1("林东平 LOGU1:%d\n",4);
//	Sleep(1000);
//
//	delete CCommonLibInit::getSingletonPtr();
////	printf("%02d\n", 2);
//	return 0;
//}

//exception
//
//// Simple implementation of an additional output to the console:
//class MyStackWalker : public StackWalker
//{
//public:
//	MyStackWalker() : StackWalker() {}
//	MyStackWalker(DWORD dwProcessId, HANDLE hProcess) : StackWalker(dwProcessId, hProcess) {}
//	virtual void OnOutput(LPCSTR szText) { printf(szText); StackWalker::OnOutput(szText); }
//};
//
//// Test for callstack of the current thread:
//void Func5() { MyStackWalker sw; sw.ShowCallstack(); }
//void Func4() { Func5(); }
//void Func3() { Func4(); }
//void Func2() { Func3(); }
//void TestCurrentThread() { Func2(); }
//
//
//// Test for callstack of an other thread:
//void TFunc5() { Sleep(10000); }
//void TFunc4() { TFunc5(); }
//void TFunc3() { TFunc4(); }
//void TFunc2() { TFunc3(); }
//DWORD WINAPI LocalThread(LPVOID) { TFunc2(); return 0; }
//void TestDifferentThread() 
//{
//	DWORD dwThreadId;
//	HANDLE hThread = CreateThread(NULL, 0, LocalThread, NULL, 0, &dwThreadId);
//	Sleep(100);  // just be "sure" that the other thread is really running...
//	MyStackWalker sw; 
//	sw.ShowCallstack(hThread);
//	CloseHandle(hThread);
//}
//
//#if _MSC_VER >= 1300
//// Test for callstack of threads for an other process:
//void TestDifferentProcess(DWORD dwProcessId)
//{
//	HANDLE hProcess = OpenProcess(
//		PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
//		FALSE, dwProcessId);
//
//	if (hProcess == NULL)
//		return;
//
//	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPALL, dwProcessId);
//	if (hSnap == INVALID_HANDLE_VALUE)
//		return;
//
//	THREADENTRY32 te;
//	memset(&te, 0, sizeof(te));
//	te.dwSize = sizeof(te);
//	if (Thread32First(hSnap, &te) == FALSE)
//	{
//		CloseHandle(hSnap);
//		return;
//	}
//
//	// Initialize StackWalker...
//	MyStackWalker sw(dwProcessId, hProcess);
//	sw.LoadModules();
//	// now enum all thread for this processId
//	do
//	{
//		if (te.th32OwnerProcessID != dwProcessId)
//			continue;
//		HANDLE hThread = OpenThread(THREAD_ALL_ACCESS, FALSE, te.th32ThreadID);
//		if (hThread == NULL)
//			continue;
//		char szTemp[100];
//		//sprintf(szTemp, "\r\nThreadID: %d\r\n", te.th32ThreadID);
//		sw.OnOutput(szTemp);  // output the threadId
//		sw.ShowCallstack(hThread);
//		CloseHandle(hThread);
//	} while(Thread32Next(hSnap, &te) != FALSE);
//}
//#endif  // _MSC_VER >= 1300
//
//
//// Exception handling and stack-walking example:
//LONG WINAPI ExpFilter(EXCEPTION_POINTERS* pExp, DWORD dwExpCode)
//{
//	MyStackWalker sw;
//	sw.ShowCallstack(GetCurrentThread(), pExp->ContextRecord);
//	return EXCEPTION_EXECUTE_HANDLER;
//}
//void ExpTest5() { char *p = NULL; p[0] = 0; }
//void ExpTest4() { ExpTest5(); }
//void ExpTest3() { ExpTest4(); }
//void ExpTest2() { ExpTest3(); }
//void ExpTest1() { ExpTest2(); }
//void TestExceptionWalking()
//{
//	__try
//	{
//		ExpTest1();
//	}
//	__except (ExpFilter(GetExceptionInformation(), GetExceptionCode()))
//	{
//	}
//}
//
//
//int _tmain()
//{
//	// 1. Test with callstack for current thread
//	//TestCurrentThread();
//
//	// 2. Test with different thread in the same process
//	TestDifferentThread();
//
//#if _MSC_VER >= 1300
//	// 3. Test with different process
//	//TestDifferentProcess(800);  // adjust the ProcessID!
//#endif
//
//	// 4. Test of walking the callstack inside an exception
//	//TestExceptionWalking();
//
//	return 0;
//}
