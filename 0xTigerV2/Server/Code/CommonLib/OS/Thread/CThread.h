/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                      
    ����˵����  �̵߳Ļ����ṹ��װ

	@2012/01/19 �ع����´���
	@2012/01/20 �о��̴߳���ܼ��ߡ�CommonLib���漸�������õ��������˲��Ե�ʱ�򿴿��߳�ʱ��
*/

#pragma once

#include <windows.h>

class CThread
{
public:
	CThread();
	virtual ~CThread();

	/*
		�û�ʵ�ֵĽӿ�
	*/
	virtual int Run()=0;	
	virtual int Exit()=0;

	/*
		ϵͳ�ӿ�
	*/
	DWORD Suspend();
	DWORD Resume();
	DWORD Join();

private:

public:
	HANDLE m_hThread;
	unsigned int   m_uThread;

private:

};