/*
	@lindp lin_style@foxmail.com   
	@2012/2/8
	@�����Ļص�����ʵ��,�����յ��������ݺ���ô�������Կ����������ϲ��һ��ճ��Ĥ��������滻����⣬
	 ֱ���޸ĸô��뼴�ɡ�
*/
#pragma  once
#include "Singleton.h"
#include "CCircleBuffer.h"

namespace net_config
{
	//�������������㣬15MB
	const int DEFAULT_BUFFER_LEN = 1024*15*1024; 

};


class CNetBridgeQueue: public Singleton<CNetBridgeQueue>
{
public:
	CNetBridgeQueue();
	~CNetBridgeQueue();

	/*
	    ����m_ToLogicQueue
		@GetLogicQueue
		    ����ֵ -1:ʧ��  0:�ɹ� 1:���Ȳ���

		@PutLogicTaskQueue
		    ����ֵ -1:ʧ��  0:�ɹ� 1:�����Ȳ�����Ҫ����Ͷ��  
	*/
	int GetLogicTaskQueue(char *pBuffer, int nBufferLen);
	int PutLogicTaskQueue(CCircleBuffer *pRecvBuffer);	
	int PutLogicTaskQueue(char *pBuffer, int nBufferLen);

	/*
		����m_ToNetQueue
		@GetNetTaskQueue
            ����ֵ -1:ʧ��  0:�ɹ� 1:���Ȳ���

		@PutNetQueue:�߼�������
		    ����ֵ -1:ʧ��  0:�ɹ� 1:���Ȳ���
	*/
	int GetNetTaskQueue(char *pBuffer, int nBufferLen);
	int PutNetTaskQueue(const char *pBuffer, int nBufferLen);	

private:
	void Init();
	void Release();

	int GetQueue(CCircleBuffer *pSrcCircleBuffer, char *pDstBuffer, int nBufferLen);

public:

private:
	/*
		@m_pLogicTaskQueue
		�߼�������У����������룬�߼���ȡ��
		@m_pNetTaskQueue
		����������У����߼�����룬�����ȡ��
	*/
	CCircleBuffer *m_pLogicTaskQueue;
	CCircleBuffer *m_pNetTaskQueue;
};

#define g_NetBridgeQueue CNetBridgeQueue::getSingleton()