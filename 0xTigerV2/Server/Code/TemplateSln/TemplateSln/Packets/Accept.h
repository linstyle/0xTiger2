/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/07/21                                                        
    ����˵����  �����ӽ���.
				ʹ���߸����Լ��Ŀ���������ʵ��Execute�ӿ�
*/

#pragma once
#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"


#define _PacketID PACKET_ACCEPT
#define _PacketClass PAccept

class PAccept:public IPackHead
{
public:
	PAccept():IPackHead(_PacketID)
	{
		STATIC_ASSERT( sizeof(_PacketClass)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PAcceptObject:public Singleton<PAcceptObject>, public IPacketObject
{
public:
	PAcceptObject():IPacketObject(_PacketID, sizeof(_PacketClass))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	/*
		pPlayLogic��ʱ�Ĳ�������Ϊ�ա��ú����ɹ��󷵻�һ��pPlayLogic��ַ��
		�Թ�CNetTransToLogic��
	*/
	virtual int	Execute(IPackHead* pPackHead, void* pPlayLogic/*==NULL*/, void* pPlayNet) ;
};