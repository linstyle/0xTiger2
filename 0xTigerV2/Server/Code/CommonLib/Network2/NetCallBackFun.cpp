#include "stdafx.h"
#include "NetCallBackFun.h"
#include "PNLInnerNotic.h"

initialiseSingleton(CNetBridgeQueue);

CNetBridgeQueue::CNetBridgeQueue()
{
	Init();
}

CNetBridgeQueue::~CNetBridgeQueue()
{
	Release();
}

void CNetBridgeQueue::Init()
{
	m_pLogicTaskQueue = new CCircleBuffer;
	m_pNetTaskQueue = new CCircleBuffer;

	m_pNetTaskQueue->Init(net_config::DEFAULT_BUFFER_LEN);
	m_pLogicTaskQueue->Init(net_config::DEFAULT_BUFFER_LEN);
}
void CNetBridgeQueue::Release()
{
//#pragma  todo �ж��Ƿ��в���İ�
	delete m_pLogicTaskQueue;
	delete m_pNetTaskQueue;
}


int CNetBridgeQueue::GetLogicTaskQueue(char *pBuffer, int nBufferLen)
{
	IF(nBufferLen!=name_msg_packet::SOCKET_BUFF_SIZE || NULL==pBuffer)
	{
		return -1;
	}

	return GetQueue(m_pLogicTaskQueue, pBuffer, nBufferLen);
}

/*
	����������
*/
int CNetBridgeQueue::PutLogicTaskQueue(CCircleBuffer *pRecvBuffer)
{
	IFn(NULL==pRecvBuffer)
	{
		return -1;
	}

	IPackHead PackHead(PACKET1_MIN,0);
	char BufferPacket[name_msg_packet::SOCKET_BUFF_SIZE]={0};

	//��ͷ�����ݴ�С�ֶ�
	if( -1==pRecvBuffer->TryReadBuffer((char*)&PackHead,  name_msg_packet::PACKET_HEAD_SIZE) )
	{
		return 1;
	}

	//���Ͷ�뵽m_ToLogicQueue
	if( -1==m_pLogicTaskQueue->WriteBufferAtom(BufferPacket, PackHead.GetPacketSize()) )
	{
		return 1;
	}
	
	//�ǵ�ˢ
	pRecvBuffer->ReadBufferFlush(PackHead.GetPacketSize());

	//���������д�ģ�������¿ռ��С���������ֱ��Ͷ�ݣ����صȵ��´�
	if (pRecvBuffer->GetUseLength()<name_msg_packet::PACKET_HEAD_SIZE * 3) 
	{
		return 1;
	}

	return 0;
}

int CNetBridgeQueue::PutLogicTaskQueue(char *pBuffer, int nBufferLen)
{
	IFn(NULL==pBuffer)
	{
		return -1;
	}

	return m_pLogicTaskQueue->WriteBufferAtom(pBuffer, nBufferLen);
}

int CNetBridgeQueue::GetNetTaskQueue(char *pBuffer, int nBufferLen)
{
	IFn(nBufferLen!=name_msg_packet::SOCKET_BUFF_SIZE || NULL==pBuffer)
	{
		return -1;
	}

	return GetQueue(m_pNetTaskQueue, pBuffer, nBufferLen);
}
int CNetBridgeQueue::PutNetTaskQueue(const char *pBuffer, int nBufferLen)
{
	IF(NULL==pBuffer)
	{
		return -1;
	}

	return m_pNetTaskQueue->WriteBufferAtom(pBuffer, nBufferLen);
}

int CNetBridgeQueue::GetQueue(CCircleBuffer *pSrcCircleBuffer, char *pDstBuffer, int nBufferLen)
{
	int nPacketIdent=0;

	IPackHead PackHead(PACKET1_MIN,0);
	if (-1==pSrcCircleBuffer->TryReadBuffer((char*)&PackHead,  name_msg_packet::PACKET_HEAD_SIZE) )
	{
		return 1;
	}

	IFn(PackHead.GetPacketSize()>nBufferLen)
	{
		LOGNE("Err, CNetBridgeQueue::GetQueue. PacketID1:%d, PacketID2:%d, PacketSize:%d\n", 
			PackHead.GetPacketDefine1(), PackHead.GetPacketDefine2(), PackHead.GetPacketSize());
		return 1;
	}

	return pSrcCircleBuffer->ReadBufferAtom(pDstBuffer, PackHead.GetPacketSize());
}