/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                        
    ����˵����  �߼����󣬻��߳�Ϊ����
*/

#pragma once

class CRole
{
public:
	unsigned int m_nRoleID;

	//char m_BufferFile[1024*1024*20];	//���20MB
	unsigned int m_nBufferFileLen;
private:

public:
	CRole()
	{
		m_nRoleID = 0;		
		m_nBufferFileLen = 0;
	}
	~CRole()
	{
		
	}

private:

};