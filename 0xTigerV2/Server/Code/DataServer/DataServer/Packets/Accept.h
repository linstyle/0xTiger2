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

class PAccept:public IPackHead
{
public:
	PAccept():IPackHead(_PacketID)
	{
		STATIC_ASSERT( sizeof(PAccept)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PAcceptObject:public Singleton<PAcceptObject>, public IPacketObject
{
public:
	PAcceptObject():IPacketObject(_PacketID, sizeof(PAccept))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	/*
		RoleObject�ڴ���Accept�¼�ʱ��ʾRoleNet����,
		�����ʾRole����
	*/
	virtual int	Execute(IPackHead* pPackHead, void* pRoleObject) ;
};