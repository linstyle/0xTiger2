/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/02/14                                                         
    ����˵����  �׽��ֵ�������������
*/

#pragma once

#include "GlobalType.h"
#include "CLock.h"
#include "CSlab.h"
#include "LinuxList.h"
#include "CNetObject.h"
#include "CNetTracer.h"
#include "ILocalObject.h"
#include "CNetTransToLogic.h"

class CSocketRun;
namespace name_socket_run
{
	struct THREAD_PARAM_ACCPET
	{
		CSocketRun *pSocketRun;
		ILocalObjectAccept *pObjectAccept;
	};
};

class CSocketRun
{
public:
	~CSocketRun();

	void Init(ILocalObjectConnect* pObjectConnect, int nConnectCount, 
			  ILocalObjectAccept* pObjectAccept, int nAcceptCount);
	void TracerMe();

	void Run();
	int  Send(CIOCPData *pIOCPKey, IPackHead *pPackHead);
	void CloseSocket(CIOCPData *pIOCPKey);

	/*
		��ȡ�ӿں���
	*/
	//�߳��Ƿ���Լ�������
	bool IsThreadRun();
private:
	/*
		��ʼ��
	*/
	bool InitIOCP();
	bool InitConnect(ILocalObjectConnect* pObjectConnect, int nConnectCount);
	bool InitAccept(ILocalObjectAccept* pObjectAccept, int nAcceptCount);
	
	/*
		��Դ֮��ľ������
	*/
	void FlushRecv();
	void FlushSend();
	void FlushIOCP();
	bool _FlushIOCP();
	void FlushConnect();
	void _FlushConnect(int nIndex);

	//send
	int AddSend(CIOCPData *pIOCPKey);
	int DelSend(CIOCPData *pIOCPKey);
	//recv
	int AddRecv(CIOCPData *pIOCPKey);
	int DelRecv(CIOCPData *pIOCPKey);
	void ResetRecv(CIOCPData *pIOCPKey);	//���½���
	//allsocket
	int AddAllSocket(CIOCPData *pIOCPKey);
	int DelAllSocket(CIOCPData *pIOCPKey);
	//iocp
	int AddIOCPPost(CIOCPData *pIOCPKey);
	int DelIOCPPost(CIOCPData *pIOCPKey);
	void IOCPPostConnect(CIOCPData *pIOCPKey);	//Ͷ��һ��IOCP�����¼�
	void IOCPPostRecv(CIOCPData *pIOCPKey);		//Ͷ��һ��IOCP�����¼�
	//connect
	int  AddLocalConnect(ILocalObjectConnect* pLocalObject);
	void DoAcceptConnect(CIOCPData *pIOCPKey);
	//accept
	void AddLocalAccept(ILocalObjectAccept* pLocalObject);
	static unsigned int WINAPI ProcAccept(void* param);
	bool StartThreadAccept();
	void EndThreadAccept();

	//ִ���ϲ��
	int ExcutePacket(CIOCPData* pIOCPKey);

	/*
		�ر�
	*/
	//�ر��׽����Լ��ϲ���߼�����
	//void CloseSocketAndLogic(CIOCPData *pIOCPKey);
	//�ر������׽�����Դ
	void CloseAllSocket();
	//�رձ����׽��ֽӿ�
	int  CloseLocalSocket(CIOCPData* pIOCPKey);

	/*
		��new��delete����Դ��װ
	*/
	CIOCPData* MallocNetObject();
	void FreeNetObject(CIOCPData* p);

	/*
		��ȡ�ӿں���
	*/
	list_head* GetListSend();
	list_head* GetListRecv();
	list_head* GetListAll();
public:

private:
	CIOCP m_IOCP;
	/*
		m_ListSendActive:��������
		m_ListRecvActive:��������
		m_ListAllSocket:�����׽��ֵ�����
	*/
	CList m_ListSendActive;
	CList m_ListRecvActive;
	CList m_ListAllSocket;

	std::vector<ILocalObjectConnect*> m_LocalObjectConnect;
	std::vector<ILocalObjectAccept*> m_LocalObjectAccept;
	std::vector<HANDLE> m_hThreadAccept;
	//�����߳��Ƿ�ִ��
	bool m_bThreadRun;		
};
