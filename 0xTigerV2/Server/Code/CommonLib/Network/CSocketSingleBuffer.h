/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/13  ��ҹ                                                         
    ����˵����  ���ɻ��λ������ĵ����ṹ
*/
#pragma once
#include <memory.h>

namespace name_socket_single_buffer
{
	const int DEFAULT_BUFFER_LEN = 1024*32; //kb
};

/*
	��������
*/
class CSingleBuffer
{
public:
	CSingleBuffer();
	~CSingleBuffer();
	void InitBuffer(int nBytes);

	bool WriteBuffer(const char* Buffer, int nLen);
	void WriteFlush(int nLen);
	/*
		ReadBuffer,ReadFlush,����һ�������Ķ�ȡ����
	*/
	const char* ReadBuffer();
	bool ReadFlush(int nLen);
	
	/*
		���ȷ����֣�һ���ǿ�д��(FreeLengthWrite)��һ����ȫ���Ŀ��г���(GetFreeLength)				
	*/
	int GetUseLength();
	int GetFreeLength();
	int GetFreeLengthWrite();
	char* GetFreeBuffer();
	const char* GetUseBuffer();

private:
	void ReSet();
	bool IsCanWrite(int nLen);
	
public:
	/*
		ָ����ͷβ�ļ�������
		m_nTail...........m_nHead
	*/
	int m_nTail;
	int m_nHead;	

private:
	char *m_pBuffer;

	int m_nBufferLen;
};