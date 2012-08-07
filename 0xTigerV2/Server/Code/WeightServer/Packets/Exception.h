/*  作者：		林东平                                                              
	创建时间：	2010/08/02                                                       
    功能说明：  网络层异常,逻辑层要做的对应处理
				使用者根据自己的开发环境，实现Execute接口
*/

#pragma once
#include "Singleton.h"
#include "IPackets.h"
#include "CPacketFactory.h"

#define _PacketID PACKET_EXCEPTION

class PException:public IPackHead
{
public:
	PException():IPackHead(_PacketID)
	{
		STATIC_ASSERT( sizeof(PException)<name_msg_packet::SOCKET_BUFF_SIZE );		
	}
};


class PExceptionObject:public Singleton<PExceptionObject>, public IPacketObject
{
public:
	PExceptionObject():IPacketObject(_PacketID, sizeof(PException))
	{
		g_PacketFactory.AddPacketObject(this);
	}

	
	virtual int	Execute(IPackHead* pPackHead, void* pPlayLogic, void* pPlayNet) ;
};