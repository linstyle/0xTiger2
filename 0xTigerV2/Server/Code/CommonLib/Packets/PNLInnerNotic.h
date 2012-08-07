/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/1/19                                                        
    ����˵����  ����㽫���ݷ����������
					   Objectʵ����Ҫ��CCmInitPackets.h�г�ʼ��ȫ��
    ����
	@2012/2/17
	����Ϊ�߼���������֮����ڲ�ͨѶЭ��
*/

#pragma once

#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

//������Ҫ�޸�
#define _PacketID1 PACKET1_INNER_NET_LOGIC


class PNLInnerNotic:public IPackHead
{
public:
	SOCKET m_nSocket;
	USHORT m_nPort;
	ULONG  m_nIP;
	//void*      m_pNetObject;  //�ƶ�����ͷ��
	bool m_bAutoConnect;

	ULONG m_ErrParam;	
	PNLInnerNotic():IPackHead(_PacketID1, sizeof(this))
	{
		m_nSocket = 0;
		m_nPort = 0;
		m_nIP = m_ErrParam = 0;
	//	m_pNetObject = NULL;
		m_bAutoConnect = true;

		STATIC_ASSERT( sizeof(PNLInnerNotic)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PNLInnerNoticObject:public Singleton<PNLInnerNoticObject>, public IPacketObject
{ 
public:
	PNLInnerNoticObject():IPacketObject(_PacketID1)
	{
		g_PacketFactory.AddPacketObject(this);
	}

	virtual int	Execute(IPackHead* pPackHead) ;
};
