/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/09                                                         
    ����˵����  �����������ɵ����ƻ��λ�����
*/
#pragma once

#include "GlobalType.h"
#include "CCircleBuffer.h"


namespace name_socket_send_buffer
{
	const int DEFAULT_BUFFER_LEN = 1024*32; //kb
};

class CSocketSendBuffer:public CCircleBuffer
{
public:
	CSocketSendBuffer(int nBufferLen = name_socket_send_buffer::DEFAULT_BUFFER_LEN);

	void TracerMe();
	/*
		д�룬��ֱ�ӵ���CCircleBuffer��WriteBuffer�ӿ�
	*/
	/*
		�����׽���������һЩ����ķ�װ
		��ȡ���ͻ����ָ��ͳ��ȣ�ֱ�ӷ��͡�
	*/
	const char* GetReadBuffer(int *pWishLen);
	void ReadBufferFlush(int nLen);

	

private:


public:

private:
};
