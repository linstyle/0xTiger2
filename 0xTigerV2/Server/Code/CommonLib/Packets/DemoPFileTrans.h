/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                        
    ����˵����  �ļ������һ������
*/
#pragma once

#include "IPackets.h"
#include "CPacketFactory.h"

//������Ҫ�޸�
#define _PacketID1 PACKET1_FILE_TRANS

//����������ݽṹ
class PFileTrans:public IPackHead
{
public:	
	char m_Buffer[1024];
	unsigned int m_BufferLen;
	bool m_bEnd;
	
	PFileTrans():IPackHead(_PacketID1, sizeof(this))
	{
		memset(m_Buffer, 0, 1024);
		m_BufferLen = 0;
		m_bEnd = false;
		
		//��Ҫ����̬�ļ��
		STATIC_ASSERT( sizeof(this)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};

//�����ʵ��Execute����
class PFileTransObject:public Singleton<PFileTransObject>, public IPacketObject
{
public:
	PFileTransObject():IPacketObject(_PacketID1)
	{
		g_PacketFactory.AddPacketObject(this);
	}

	
	virtual int	Execute(IPackHead* pPackHead, void* pRole) ;
};