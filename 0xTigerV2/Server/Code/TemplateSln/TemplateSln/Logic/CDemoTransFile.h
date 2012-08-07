/*  作者：		林东平                                                              
	创建时间：	2010/08/03                                                         
    功能说明：  文件传输DEMO代码
*/
#pragma once

#include "md5.h"
#include <string>
#include <stdio.h>
#include "DemoPFileTrans.h"
using namespace std;

class CDemoTransFile
{
public:
	CDemoTransFile();
	~CDemoTransFile();
	bool OpenFile();
	
	/*
		返回一个读的长度，
		-1: 出错
		小于Len :文件末尾
	*/
	int ReadContent(char* Buffer, unsigned int Len);

	void TracerMe();

private:
	/*
		获取文件校验值
	*/
	void MD5Value();
	
public:	

private:
	int m_nReadOffset;

	FILE *m_pFile;
	char *m_pBuffer;
	string m_strMD5;

	int m_nFileLen;
	int m_nCountSend;
	int m_nCountHasSend;
};