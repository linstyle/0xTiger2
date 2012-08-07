/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/06/21                                                      
    ����˵����  �̵߳Ļ����ṹ��װ
*/

#pragma once

#include <windows.h>


class IThread
{
public:
	IThread()
	{
		m_dwUserHeartBeat = m_dwUserHeartBeatOld = 0;
	}
	virtual ~IThread()
	{
	}

	virtual int Run()=0;	
	virtual int Exit()=0;


	/*
		��������:�����û�Ӧ�����Ƿ��ڻ״̬����Ҫ�û��ж��Լ������runѭ�����һ����Ҫ������ӡ�
				 Ҫע����DWORD�ķ�Χ����һ���Ƶ��ִ�����㣬32λ���ϵ�DWORD��������136��(2^32)��ʱ�䡣
	*/
	void UserHeartBeat()
	{
		++m_dwUserHeartBeat;
	}


	/*
		��������:�û�Ӧ�����Ƿ��ڻ״̬
		��������:true,�
				 false, �ǻ
	*/
	bool UserIsActivity ()
	{
		if( m_dwUserHeartBeat>m_dwUserHeartBeatOld )
		{
			m_dwUserHeartBeatOld = m_dwUserHeartBeat;
			return true;
		}
		
		return false;
	}

private:

public:

private:
	DWORD m_dwUserHeartBeat;
	DWORD m_dwUserHeartBeatOld;

};




class CThread
{
public:
	CThread();
	~CThread();
	DWORD Suspend()
	{
		return SuspendThread(m_hThread);
	}
	DWORD Resume()
	{
		return ResumeThread(m_hThread);
	}
	DWORD Join()
	{
		return WaitForSingleObject(m_hThread, INFINITE);
	}


private:

public:
	HANDLE m_hThread;
	unsigned int   m_uThread;
	DWORD m_dwStartTime;

private:
	
};