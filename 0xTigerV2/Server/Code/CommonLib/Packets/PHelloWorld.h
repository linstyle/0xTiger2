/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2012/3/12                                                        
    ����˵����  �Ե�½�Ķ��󣬶��ᷢ��һ��hello world
					   Objectʵ����Ҫ��CCmInitPackets.h�г�ʼ��ȫ��
*/

#pragma once


#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

//������Ҫ�޸�
#define _PacketID1 PACKET1_HELLO


class PHelloWorld:public IPackHead
{
public:
	char m_Buffer[512];
	PHelloWorld():IPackHead(_PacketID1, sizeof(this))
	{
		STATIC_ASSERT( sizeof(PHelloWorld)<name_msg_packet::SOCKET_BUFF_SIZE );		
		memset(m_Buffer, 0, sizeof(m_Buffer));
	}
};


class PHelloWorldObject:public Singleton<PHelloWorldObject>, public IPacketObject
{ 
public:
	PHelloWorldObject():IPacketObject(_PacketID1)
	{
		g_PacketFactory.AddPacketObject(this);
	}

	virtual int	Execute(IPackHead* pPackHead) ;
};