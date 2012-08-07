/*  作者：		林东平                                                              
	创建时间：	2010/06/21                                                      
    功能说明：  线程的基本结构封装
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
		函数功能:监视用户应用上是否处于活动状态。需要用户判断自己程序的run循环里，哪一处需要进行添加。
				 要注意下DWORD的范围，按一秒的频率执行来算，32位机上的DWORD可以容纳136年(2^32)的时间。
	*/
	void UserHeartBeat()
	{
		++m_dwUserHeartBeat;
	}


	/*
		函数功能:用户应用上是否处于活动状态
		函数返回:true,活动
				 false, 非活动
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