#pragma once

#include "0x_Exception.h"
#include "0x_Network.h"

namespace name_routemsg_protocol
{	
	const int ROUTE_ORADER_ACTION_MAX = 3;	//PostofficeServer
};

class MsgServerLogin:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=1,		//��ʾһ�����ද���ı�־
		DoAction=0			//��ʾ����ִ�еĶ���	
	};
	int nBinIdenti;


public:
	MsgServerLogin()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;

		nBinIdenti = -1;
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgServerLogin)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};

class MsgServerUpdatePeople:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=2,		//��ʾһ�����ද���ı�־
		DoAction=0			//��ʾ����ִ�еĶ���	
	};

	int nBinIdenti;
	int nPort;
	unsigned long nIP;
	int nPeople;

public:
	MsgServerUpdatePeople()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;

		nBinIdenti = nPeople = nPort = nIP = 0;
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgServerUpdatePeople)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};