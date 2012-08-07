/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                        
    功能说明：  逻辑对象，或者称为人物
*/

#pragma once

class CRole
{
public:
	unsigned int m_nRoleID;

	//char m_BufferFile[1024*1024*20];	//最大20MB
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