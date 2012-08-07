/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                        
    功能说明：  逻辑对象，或者称为人物
*/

#pragma once

class CRole
{
public:
	/*
		debug:测试被调用次数和网络对象的socket值
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