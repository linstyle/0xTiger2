/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                        
    ����˵����  �߼����󣬻��߳�Ϊ����
*/

#pragma once

class CRole
{
public:
	/*
		debug:���Ա����ô�������������socketֵ
	*/
	unsigned int m_nByCallCount;
	unsigned int m_nRecordSocket;
private:

public:
	CRole()
	{
		m_nRecordSocket = 0;
		m_nByCallCount = 0;
	}
	~CRole()
	{
		
	}

private:

};