/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2012/3/7                                                        
    ����˵����  GS��LS��½
					   Objectʵ����Ҫ��CCmInitPackets.h�г�ʼ��ȫ��
*/

#pragma once

#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

//������Ҫ�޸�
#define _PacketID1 PACKET1_LOGIN_GL


class PLogin:public IPackHead
{
public:

	PLogin():IPackHead(_PacketID1, sizeof(this))
	{

		STATIC_ASSERT( sizeof(PLogin)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PLoginGLObject:public Singleton<PLoginGLObject>, public IPacketObject
{ 
public:
	PLoginGLObject():IPacketObject(_PacketID1)
	{
		g_PacketFactory.AddPacketObject(this);
	}

	virtual int	Execute(IPackHead* pPackHead) ;
};
