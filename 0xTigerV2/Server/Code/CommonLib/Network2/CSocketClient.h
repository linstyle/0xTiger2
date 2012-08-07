/*
	@lindp lin_style@foxmail.com   
	@2012/1/24
	@��д���������֮������ͻ��˶���
*/
#pragma  once

#include "LinuxList.h"
#include "CWindowsSlabManager.h"
#include "CCircleBuffer.h"
#include "CLog2.0.h"
/*
	����ռ��ȫ��API
*/
class CSocketClient;
CSocketClient* MallocSocketClientObject();
void FreeSocketClientObject(CSocketClient* p);

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

enum IOCP_STEP_FLAG
{
	IOCP_STEP_ERR,
	IOCP_STEP_INIT,  //��ʼ��״̬
	IOCP_STEP_RECV_ING,
	IOCP_STEP_RECV_COMPLATE,
	IOCP_STEP_CONNECT,
};

namespace socket_circle_config
{
	const int RECV_CIRCLE_LEN = 16*1024;  //kb, ϵͳĬ���׽�����8KB��������С���ɡ�
	const int SEND_CIRCLE_LEN = 16*1024; //kb��������ҵ���й�
};


class CSocketClient
{
public:
	CSocketClient();
	~CSocketClient();

	void Init();

	int Connect();
	int Recv();
	int Send(const char* pBuffer, int nBufferLen);
	int FlushSend();

private:
	/*
		@send,recv,connect����
	*/
	bool InitConnect();
	int FlushSendSub();
	int RecvPacketStream();
	void InitRecv();
	void InitRecv1();
	void InitRecv2();

public:
	SOCKET m_nSocket;
	USHORT m_nPort;
	ULONG  m_nIP;	

	/*
		connect
	*/
	sockaddr_in m_ConnectAddr;
	bool m_bAutoConnect; //�����Ϊtrue,�򲻻�������ɾ�����Ͽ�ʱ���Զ�����
	
	/*
		��ɶ˿���Ҫ�ı����Լ�������
	*/
	DWORD m_nRecvBytes;
	DWORD m_nWSARecvFlag;
	WSABUF m_WSADataBuf[2];
	WSAOVERLAPPED  m_OverlappedRecv;
	IOCP_EVENT_TYPE m_nIOCPEvent;
	CCircleBuffer m_RecvBuffer;
	CCircleBuffer m_SendBuffer;
	/*
		��ʾ��ǰ��Ҫ����Ķ���
		-1:��ʾ����
		0:��recvͶ����
		1:Ͷ�����
		2:��Ҫ����
	*/
	IOCP_STEP_FLAG m_nStepFlag;

	struct list_head m_List;
private:

};

