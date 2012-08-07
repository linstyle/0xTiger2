#pragma once
#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

#define _PacketID PACKET_HELLO

class PHelloWorld:public IPackHead
{
public:
	DWORD nTimeSec;
	DWORD nTimeSec1;
	char buffer[100];
	PHelloWorld():IPackHead(_PacketID)
	{
		nTimeSec = GetTickCount();
		STATIC_ASSERT( sizeof(PHelloWorld)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PHelloWorldObject:public Singleton<PHelloWorldObject>, public IPacketObject
{
public:
	PHelloWorldObject():IPacketObject(_PacketID, sizeof(PHelloWorld))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	
	virtual int	Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet) ;
};