#pragma once
#include "0x_Exception.h"
#include "0x_Network.h"
/*
  一些共同的字段上，名字不变
  服务器向客户端返回使用的字段前面加"_"

*/
namespace name_playmsg_protocol
{	
	const int PLAY_ORADER_ACTION_MAX = 3;	//PostofficeServer
};



class MsgClientAskEncryption:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=2,		//表示一个大类动作的标志
		DoAction=0			//表示真正执行的动作	
	};
	/*
		如果nPort和nIP都为零，表示获取失败
	*/
	int _nPort;
	unsigned long _nIP;
	char _strEncry[256];	//客户端IP+客户端PORT+邮局服务器IP+邮局服务器PORT+时间

public:
	MsgClientAskEncryption()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;

	    _nPort = _nIP = 0;		 
		memset(_strEncry, 0, 256);
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgClientAskEncryption)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}	
};

