/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/08/02                                                       
    ����˵����  ������쳣,�߼���Ҫ���Ķ�Ӧ����
				ʹ���߸����Լ��Ŀ���������ʵ��Execute�ӿ�
*/

#pragma once
#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

#define _PacketID PACKET_EXCEPTION
#define _PacketClass PException

class PException:public IPackHead
{
public:
	PException():IPackHead(_PacketID)
	{
		STATIC_ASSERT( sizeof(_PacketClass)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PExceptionObject:public Singleton<PExceptionObject>, public IPacketObject
{
public:
	PExceptionObject():IPacketObject(_PacketID, sizeof(_PacketClass))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	
	virtual int	Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet) ;
};