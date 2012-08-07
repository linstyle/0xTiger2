/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/13  ��ҹ                                                         
    ����˵����  �����������ɵ����ƻ��λ�����
*/
#pragma once

#include "GlobalType.h"
#include "CCircleBuffer.h"

namespace name_socket_recv_buffer
{
	const int DEFAULT_BUFFER_LEN = 1024*32; //kb
};

class CSocketRecvBuffer:public CCircleBuffer
{
public:
	CSocketRecvBuffer(int nBufferLen = name_socket_recv_buffer::DEFAULT_BUFFER_LEN);

	void TracerMe();

	/*
		һЩ���������:
		1.IOCP��Ҫֱ�ӶԵ�ַ����д�룬���Կ���GetWriteBuffer1��GetWriteBuffer2�ӿ�
		2.�ڲ����ʱ���Ϊ��ͷ�Ͱ������β�֣���ǰ������ǰ�ͷ+���嶼��ȡ�ɹ��ˣ���
		  ��Ϊһ�������Ĳ��������β�ֵ�����²���֪����ǰ�������ĳ����Ƿ���ȷ�������ṩ
		  һ��TryReadBuffer�Ľӿڣ�����ˢ���ύ�Ķ�����

		  �������������󶼲�����ֶ��̵߳Ĳ�������		
	*/
	char *GetWriteBuffer1(int *pLen);
	char *GetWriteBuffer2(int *pLen);
	void WriteBufferFlush(int nLen);

	/*
		��ʵ���Ǹ������桢���ύˢ�µĵ�ReadBuffer
	*/
	int TryReadBuffer(char *Buffer, int nLen);
	void ReadBufferFlush(int nLen);

private:

public:


private:	
};
