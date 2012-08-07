#pragma once
#include <memory.h>
#include "ProtocolHead_Pack.h"
//#包大小后期优化
class MsgBaseHead
{
public:	
	int nSizeOfMsg;		//整个数据包的大小，包括头部
	int __nActionOrder;	
	int __nActionDo;
	
	/*
		nDoPriority
		执行优先等级,0-5,越低表示权限越高. (默认为3)
	*/
	int nDoPriority;

	/*
		nRoutePriority
		路由转发的等级, 需要手动设置
		0:路由自身执行命令(默认)
		1:bin转发命令		
		2:dpc转发命令
		3:转发客户端00000000
		4:其他。。。。。
		2010:关闭
	*/
	int nRoutePriority;

	/*
		debug,字段
	*/
	int nInBinPoolRes;//暂时为0

public:
	MsgBaseHead()
	{
		nDoPriority = 3;
		nRoutePriority = 0;

		nInBinPoolRes = 0;
	}
};

/*
	建立连接后，由客户端向服务端进行发送该问候
*/
class MsgSayHello:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=0,
		DoAction=0		
	};

	char Buffer[256];

public:
	MsgSayHello()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;
		nSizeOfMsg = sizeof(*this);	
		memset(Buffer, 0, 256);
	}

};

namespace name_msg_protocol
{	
	const int MSG_HEAD_BASE_SIZE = sizeof(MsgBaseHead);	
	const int SOCKET_BUFF_SIZE = 768;
	const int SOCKET_BUFF_SIZE_EX = SOCKET_BUFF_SIZE + name_protocol_pack::PACK_BUFF_SIZE;
};

