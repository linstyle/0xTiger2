/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/03                                                         
    ����˵����  �ļ�����DEMO����
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
		����һ�����ĳ��ȣ�
		-1: ����
		С��Len :�ļ�ĩβ
	*/
	int ReadContent(char* Buffer, unsigned int Len);

	void TracerMe();

private:
	/*
		��ȡ�ļ�У��ֵ
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