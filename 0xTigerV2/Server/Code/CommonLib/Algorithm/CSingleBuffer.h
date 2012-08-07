/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/13  ��ҹ                                                         
    ����˵����  ���ɻ��λ������ĵ����ṹ
*/
#pragma once
#include <assert.h>
#include <stdio.h>
#include <memory.h>

/*
	��������
*/
class CSingleBuffer
{
public:
	CSingleBuffer();
	~CSingleBuffer();
	void InitBuffer(int nBytes);

	/*
		Ϊ��Ӧ���ֲ�ͬ���첽��ȡ����һ�������Ķ������write,flush.ֻ��ִ��flush�����һ��������
		��������flush�Ľӿ��ϣ���������Ϊһ��void���������е�ԭ���ԡ�
		���԰Ѹ������ΪSingleBuffer,���û������·�װ���Լ���Ҫ�Ĺ���
	*/
	void WriteBuffer(const char *Buffer, int nLen);
	void WriteFlush(int nLen);
	bool IsFull();

	void ReadBuffer(char *Buffer, int nLen);
	void ReadFlush(int nLen);
	bool IsEmpty();

	/*
		UseLength,��ǰ��������Ч����
		FreeLength,��ǰ������ȫ�����г���
		FreeLengthWrite,��ǰ��������Ч���г���
		��λ:bytes
	*/
	int GetUseLength();
	int GetFreeLengthWrite();

	/*
		��ʱ����Ҫֱ�ӱ�¶��ַ�ռ�
	*/
	char* GetFreeBuffer();
	char* GetUseBuffer();

private:
	void ReSet();
	
public:	

private:
	/*
		ָ����ͷβ�ļ�������
		m_nTail...........m_nHead
	*/
	int m_nTail;
	int m_nHead;

	char *m_pBuffer;

	int m_nBufferLen;
};