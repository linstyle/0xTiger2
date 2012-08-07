/*  
	���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/11/3                                                        
    ����˵����  �߼��׽��֣������Ѿ����ڼ���״̬���׽���
*/
#pragma once

#include "GlobalType.h"
#include "CLock.h"
#include "CSlab.h"
#include "LinuxList.h"
#include "CNetObject.h"
#include "CNetTracer.h"
#include "CNetTransToLogic.h"

class CSocketLogic
{
public:
	CSocketLogic();
	~CSocketLogic();

	void TracerMe();

	/*
		ע�⣬FlushExceptionֻ��SocketPhysical�е�һ���Ӽ�
	*/
	void FlushRecv();
	void FlushSend();
	void FlushException(CIOCPData *pIOCPKey);
	void CloseAllSocket();				//�ر������߼��׽���

	int AddRecv(CIOCPData *pIOCPKey);
	int AddSend(CIOCPData *pIOCPKey);
	void AddException(CIOCPData *pIOCPKey, LONG nLastCount);
	
	list_head* GetListException();
private:
	/*
		DelSend,DelRecvֻ�Ǵ�����ɾ��,Ȼ����ص�Exception��
		DelException���׻�����Դ
		Exception��������˼�����֣�һ���������ĶϿ��������쳣�����ݴ���ȡ����ﶼ��Ϊ
				 �ײ�����һ���쳣(���﷨�������)�����������µ���Ϊ���ǻ�����Դ
	*/
	void DelSend(CIOCPData *pIOCPKey, bool bException=false);
	void DelRecv(CIOCPData *pIOCPKey, bool bException=false);
	void DelException(CIOCPData *pIOCPKey);
	void ResetActiveRecv(CIOCPData *pIOCPKey);

	int ExcutePacket(CIOCPData* pIOCPKey);
	int ClosePacket(CIOCPData* pIOCPKey);

	list_head* GetListSend();
	list_head* GetListRecv();
	
	
public:
	/*
		Ϊ�˼�,m_ListSendActiveʵ�����������׽��ֵ�һ������(���̷߳�)��
		��ʹ��������׽������ݺ�Ҳ�����������ɾ��
	*/
	CList m_ListSendActive;
	CList m_ListRecvActive;
	CList m_ListExceptionActive;
	
private:

};

