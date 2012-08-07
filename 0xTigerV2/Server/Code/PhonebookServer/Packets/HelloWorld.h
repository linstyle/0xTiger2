#pragma once
#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

#define _PacketID PACKET_HELLO
#define _PacketClass PHelloWorld

class PHelloWorld:public IPackHead
{
public:
	DWORD nTimeSec;
	DWORD nTimeSec1;
	char buffer[100];
	_PacketClass():IPackHead(_PacketID)
	{
		nTimeSec = GetTickCount();
		STATIC_ASSERT( sizeof(_PacketClass)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PHelloWorldObject:public Singleton<PHelloWorldObject>, public IPacketObject
{
public:
	PHelloWorldObject():IPacketObject(_PacketID, sizeof(_PacketClass))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	
	virtual int	Execute(IPackHead* pPackHead, void* pRoleObject) ;
};