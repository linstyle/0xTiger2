/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/09/24                                                         
    ����˵����  ʱ���ftime
	2011/08/13
	�޸��½ӿڣ���GetXX��ʾ
	YY:�� MM:�� DD:�� HH:Сʱ MM:�� SS:��
*/

#pragma once
#include <memory.h>
#include <sys/timeb.h>
#include <time.h>
#include <stdio.h>

struct TIMEW_HHMMSS
{
	TIMEW_HHMMSS()
	{
		memset(m_Buffer, 0, sizeof(m_Buffer));
	}
	wchar_t m_Buffer[16];
};

struct TIME_HHMMSS
{
	TIME_HHMMSS()
	{
		memset(m_Buffer, 0, sizeof(m_Buffer));
	}
	char m_Buffer[16];
};

class CTime
{
public:
	//���������������ʱʱ�ַ�
	static unsigned long GetYYMMDDHHMM();       
	//����ʱ
	static unsigned long GetMMDDHH();  
	//ʱ����
	static TIMEW_HHMMSS* GetWHHMMSS(TIMEW_HHMMSS *pTimeWHHMMSS);  
	//ʱ����
	static TIME_HHMMSS* GetHHMMSS(TIME_HHMMSS *pTimeHHMMSS);  
	//��õ�ǰ��Сʱ
	static unsigned long GetHH();
	//����룬��1970�꿪ʼ
	static __time64_t GetSS();		
	//��ú��룬��1970�꿪ʼ
	static __time64_t GetMilli();		

private:

public:

private:

};
