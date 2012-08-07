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
		pPlayLogic这时的参数还是为空。该函数成功后返回一个pPlayLogic地址，
		以供CNetTransToLogic绑定
	*/
	virtual int	Execute(IPackHead* pPackHead, void* pPlayLogic/*==NULL*/, void* pPlayNet) ;
};