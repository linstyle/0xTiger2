/*  作者：		林东平                                                              
	创建时间：	2011/02/25                                                        
    功能说明：  逻辑对象，或者称为人物
*/


#pragma once

/*
	文件传输的CRoleLogic DEMO
*/
#include <stdio.h>
#include <string>
#include "md5.h"


using namespace std;
namespace name_role
{
	const int BUFFER_SIZE = 1024*1024; //byte
}

class CRoleLogic
{
public:
	CRoleLogic();
	~CRoleLogic();
	void Init();
	

	/*
		接收数据长度和指针，如果当前缓冲区不够容纳，会自动调用
		FlushHD刷新到磁盘。
	*/
	void Recv(const char* pBuffer, int nSize);
	/*
		刷新到磁盘
	*/
	void FlushHD();
	
private:
	//md5校验
	void VerifyMD5();
	
	void InitSavaTerminalW();	//写入
	void InitSavaTerminalR();	//读取
	void CloseSaveTerminal();
	void _FlushHD();

public:
	char m_BufferFile[name_role::BUFFER_SIZE];
	int m_nHasRecvLen;
	FILE *m_pFile;

private:
	char m_SavaTerminalName[128];	//保存的文件名
};