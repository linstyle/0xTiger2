/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/19  ҹ                                                         
    ����˵����  ���λ������������˫�����ʺ��׽��ֽṹ
*/
#pragma once
#include "CLock.h"
#include "CSingleBuffer.h"

class CCircleBuffer
{
public:
	CCircleBuffer(int nBufferLenBytes);
	CCircleBuffer();
	~CCircleBuffer();

	void Init(int nBufferLenBytes); //KB
	/*
		WriteBuffer
		����ֵΪ-1����0�� ������Ϊд���ʵ�ʳ��ȡ�������ɻ��������ȿ��ơ�
		�����㹻�ĳ��ȣ������д������ֱ�Ӷ��������������ӵĴ���
	*/
	int WriteBuffer(const char*Buffer, int nLen);

	/*
		ReadBuffer
		����ֵΪ������ȡ����������,�ó���С�ڵ��ڲ���nLen
	*/
	int ReadBuffer(char *Buffer, int nLen);

	/*
		����ʹ�ó���
	*/
	int GetUseLength();

private:	
	void WriteBufferFlush(int nLen);
	void ReadBufferFlush(int nLen);

public:

private:
	int m_nWriteIndex;
	int m_nReadIndex;

	CSingleBuffer m_SingleBuffer[2];
	/*
		���λ�������һ���̶߳���һ���߳�д�����У�����Ҫ����
		���һ��������д�Ķ���������߳�ִ�У���Ҫ����
	*/
	CFastLock m_LockWrite;
	CFastLock m_LockRead;


};
