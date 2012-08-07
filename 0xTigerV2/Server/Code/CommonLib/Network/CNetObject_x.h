/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/20                                                        
    ����˵����  �������
*/
#pragma once
#include "CSocketAPI.h"
#include "IPackets.h"
#include "ListArrayMap.h"
#include "CLock.h"
#include "LinuxList.h"
#include "CSocketSendBuffer.h"
#include "CSocketRecvBuffer.h"

enum IOCP_EVENT_TYPE
{
	/*
		iocp�õ�����ʵ��CONNECT, BIG
	*/
	IOCP_EVENT_ACCEPT_CONNECT,
	IOCP_EVENT_RECV_HEAD,
	IOCP_EVENT_RECV_CONTENT,
	IOCP_EVENT_RECV_BIG,
	IOCP_DEBUG_NEW,
	IOCP_DEBUG_FREE
};

/*
	����λ�ñ�ʶ
*/
class CBelongToList
{
public:
	CBelongToList();
	
	void SetSendList(bool b);
	void SetRecvList(bool b);
	void SetIOCPPost(bool b);
	void SetAllSocketList(bool b);

	bool IsSendList();
	bool IsRecvList();
	bool IsIOCPPost();
	bool IsAllSocketList();

private:
	void Init();

public:

private:
	bool m_bSendList;
	bool m_bRecvList;
	bool m_bIOCPPost;	//Ͷ��IOCP��
	bool m_bAllSocket;
};


class CIOCPData:public CKeyId/*ListArrayMap*/
{
public:
	CIOCPData();
	~CIOCPData();

	void Init();
	/*
		Send()
		����ֵ:
				1: û��ȫ������
				0: ȫ������
			   -1: ����
	*/	
	int Send(IPackHead *pPackHead);	//SendBufferWrite()
	int FlushSend();				//SendBufferFlushRead();
	
	/*
		���յ�˳��:��ȡЭ��ͷ����ȡ���ݳ��ȣ�����Э������
		RecvPacketHead
		InitRecvPacketContent
		RecvPacketContent

		Recv(); �����ϵĶ�
		RecvPacketHead, RecvPacketContent;�߼��ϵĶ����ӻ������ϣ�
	*/
	int Recv();
	int RecvPacketHead();
	int RecvPacketContent(unsigned int nLen);
	int InitRecvPacketContent();
	void FlushRecv(unsigned int nLen); //RecvBufferFlushWrite();

private:
	int FlushSendSub();
	int RecvPacket();

	void InitRecv();
	void InitRecv1();
	void InitRecv2();

public:
	/*
		��ɶ˿���Ҫ�ı����Լ�������
	*/
	SOCKET nSocket;
	DWORD nRecvBytes;
	DWORD nWSARecvFlag;
	WSABUF WSADataBuf[2];
	WSAOVERLAPPED  OverlappedRecv;

	/*
		BufferPacket:ÿ��������Ĵ�С���
	*/
	char BufferPacket[name_msg_packet::SOCKET_BUFF_SIZE];
	CSocketRecvBuffer RecvBuffer;
	CSocketSendBuffer SendBuffer;
	
	IOCP_EVENT_TYPE nEvent;

	CBelongToList BelongToList;

	struct list_head m_ListSend;
	struct list_head m_ListRecv;
	struct list_head m_ListAllSocket;
private:
};
