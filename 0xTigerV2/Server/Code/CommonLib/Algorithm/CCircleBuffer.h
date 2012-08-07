/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/19  ҹ                                                         
    ����˵����  ���λ�������֧�ֶ��̵߳Ķ���д���ڶ���д��һ���߳�ʱ����������
	            ���߳��»��кܴ��Ż��ռ䣬���Բ��е�д�룬�ݲ�ʵ��

	@���� 2012/2/12
	api���ࡣʹ���з��֣�����Ҫ��api��¶��Ҫ���࣬
	һ���ǽ��ڲ�ָ�뱩¶�������ٿ���:(��֧�ֶ��߳�)
	    write,����WSARecv����ֱ�ӹҹ�ָ��ռ�.������flush�ӿ�
		read,����д����־��send�ӿڣ�ֻ����ȡ�����ٺ�ָ����������

	�����������ڲ�ʵ�֣�����ռ�ͳ��ȵȲ��������п���:(֧�ֶ��߳�)
	    ��ͨ��д��
		�������е㲻һ����ֻ��һ��"͵��"�Ķ���

	�����漰�����Ĳ�������������ʵ���ϵĴ���ֿ�����Ȼ���ࣩ
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
		һ��API���֣���Ҫ���flushʹ��.������Ϊ��ָ��ı�¶���󣬲�֧�ֶ��߳�
	*/
	char *GetWriteBuffer1(int *pLenBytes);
	char *GetWriteBuffer2(int *pLenBytes);
	void WriteBufferFlush(int nWriteLenBytes);

	char* GetReadBuffer(int *pWishLenBytes);
	int TryReadBuffer(char *pBuffer, int nReadLenBytes);
	void ReadBufferFlush(int nReadLenBytes);

	/*
		����API���֣�����atom���֣���ʾ�Ǹ�ԭ�Ӳ�����֧�ֶ��߳�
	*/
	/*
		WriteBuffer
		����ֵΪ-1����0�� Ҫôд�ɹ���Ҫôʧ��

		ReadBufferAtom
		����ֵΪ-1����0�� Ҫô���ɹ���Ҫôʧ��
	*/
	int WriteBufferAtom(const char* pBuffer, int nWriteLenBytes);
	int ReadBufferAtom(char* pBuffer, int nReadLenBytes);


	int GetUseLength();
private:
	


protected:

public:
	int m_nWriteIndex;
	int m_nReadIndex;

	CSingleBuffer m_SingleBuffer[2];
	/*
		��о
	*/
	CFastLock m_LockWrite;
	CFastLock m_LockRead;
};
