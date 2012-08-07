/*  作者：		林东平                                                              
	创建时间：	2010/07/21                                                        
    功能说明：  新连接接收.
				使用者根据自己的开发环境，实现Execute接口
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
		RoleObject在处理Accept事件时表示RoleNet对象,
		否则表示Role对象
	*/
	virtual int	Execute(IPackHead* pPackHead, void* pRoleObject) ;
};