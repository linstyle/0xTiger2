#include "StdAfx.h"
#include "CDemoTransFile.h"



CDemoTransFile::CDemoTransFile()
{
	m_pFile = NULL;
	m_nFileLen = 0;
	m_nReadOffset = 0;

	MTVERIFY( true==OpenFile() );
	printf("Notic, File Len:%d,  MD5:%s\n", m_nFileLen, m_strMD5.c_str());

	m_nCountHasSend = 0;
	m_nCountSend = m_nFileLen / 1000;
	if( (m_nFileLen-1000*m_nCountSend) > 0 )
	{
		m_nCountSend+=1;
	}
}

CDemoTransFile::~CDemoTransFile()
{
	if( NULL!=m_pFile )
	{
		fclose(m_pFile);
	}

	delete []m_pBuffer;
}

void CDemoTransFile::TracerMe()
{
	printf("Notice CDemoTransFile\n");
	printf("File Transing:%d  /  %d\n", ++m_nCountHasSend, m_nCountSend);
}

bool CDemoTransFile::OpenFile()
{
	m_pFile = fopen("DemoTransFile.ncb", "rb");
	if( NULL==m_pFile )
	{
		printf("Err, OpenFile Failed:%d\n", GetLastError());
		return false;
	}

	/*
		求出长度
	*/
	fseek(m_pFile, 0, SEEK_END);
	m_nFileLen = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	m_pBuffer = new char[m_nFileLen];
	fread(m_pBuffer, 1, m_nFileLen, m_pFile);

	MD5Value();

	return true;
}

void CDemoTransFile::MD5Value()
{
	m_strMD5 = CMD5::MD5(m_pBuffer, m_nFileLen);
}
	


int CDemoTransFile::ReadContent(char* Buffer, unsigned int Len)
{
	unsigned int nMemCpyLen;
	/*
		判断剩余空间是否够读
	*/
	if( (m_nFileLen-m_nReadOffset)>=Len )
	{
		nMemCpyLen = Len;
	}
	else
	{
		nMemCpyLen = (m_nFileLen-m_nReadOffset);
	}

	memcpy(Buffer, &m_pBuffer[m_nReadOffset], nMemCpyLen);
	m_nReadOffset += nMemCpyLen;

	return nMemCpyLen;
}