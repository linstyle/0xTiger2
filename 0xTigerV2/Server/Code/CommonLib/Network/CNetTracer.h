/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/20                                                        
    ����˵����  ����DEBUG��¼
*/

#pragma once

#include "GlobalType.h"
#include "CLock.h"

class CNetTracer
{
public:
	CNetTracer()
	{
		/*
			m_nAccept;		��ǰ������	
			m_nAcceptErr;	�����������
			m_nConnectDis;	�����Ĵ���
			m_nConnectErr;	��������Ӵ���
		*/
		m_nAccept = m_nAcceptErr = m_nConnectDis = m_nConnectErr = 0;
		m_nRecv = m_nSend = m_nRecvSec = m_nSendSec = 0;
	}

	CAtom m_nAccept;
	CAtom m_nAcceptErr;
	CAtom m_nConnectDis;
	CAtom m_nConnectErr;
	CAtom m_nRecv;
	CAtom m_nSend;	
	/*
		ÿ�����
	*/
	CAtom m_nRecvSec;
	CAtom m_nSendSec;

	void Tracer()
	{
		DELAY_CONTINUE(5000)
		{
			printf("Notice:AC:%d, AErr:%d, CDis:%d, CErr:%d, RecvS:%d, Sends:%d\n",
				m_nAccept.GetValue(), m_nAcceptErr.GetValue(), m_nConnectDis.GetValue(),
				m_nConnectErr.GetValue(), m_nRecv.GetValue(), m_nSend.GetValue());		
		}

		TracerSec();;
	}

	void TracerSec()
	{	
		DELAY_CONTINUE(1000)
		{
			printf("Notice:RecvSec:%d, SendSec:%d\n", m_nRecvSec.GetValue(), m_nSendSec.GetValue());
			m_nRecvSec = 0;
			m_nSendSec = 0;	
		}
	}
};

extern CNetTracer g_NetTracer;