#pragma once

#include "Protocol/ProtocolHead.h"

namespace name_bpmsg_protocol
{
	/*
		如果是本地执行命令序列不变，把转发命令放置在最后
	*/
	const int BP_ORADER_ACTION_MAX = 3;
};

/*
	逻辑服务器bin登陆
*/
class MsgServerLoginBin:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=1,
		DoAction=0
	};
	/*
		nLine: 线的编号
		nBinIdenti: 线内的唯一ID
	*/
	int nLineIdenti;
	int nBinIdenti;	

public:
	MsgServerLoginBin()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;
		
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT( sizeof(MsgServerLoginBin)<name_msg_protocol::SOCKET_BUFF_SIZE );
	}
};

/*
	逻辑服务器dpc登陆
*/
class MsgServerLoginDpc:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=1,
		DoAction=1	
	};
	int nDpcIdenti;

public:
	MsgServerLoginDpc()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;
		
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgServerLoginDpc)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};

/*
	1.p->g,g去db验证
	2.db通过，返回轻量数据给g,全部数据给m
	3.m在一个临时队列里建立该角色，并且等待g数据的资源更新
	4.g返回该角色资源编号、网关编号给m
	5.m临时队列里条件满足，将该角色资源编号给网关
	6.开始通讯
*/
//class MsgClientLogin:public MsgBaseHead
//{
//public:
//	enum
//	{
//		OrderAction=2,
//		DoAction=0
//	};
//	/*
//	用户名，密码
//	*/
//	char User[20];
//	char Passwd[40];
//
//public:
//	MsgClientLogin()
//	{
//		__nActionOrder = OrderAction;
//		__nActionDo = DoAction;
//
//		nSizeOfMsg = sizeof(*this);	
//		STATIC_ASSERT(sizeof(MsgClientLogin)<name_msg_protocol::SOCKET_BUFF_SIZE);
//	}
//};

/*

*/

class MsgUpdateTest1:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=2,
		DoAction=0
	};
	/*
		nIdentiInPostoffice:	所在的网关索引
		nInPostSocket:	在Postoffice中的套接字信息
		nResIdentiInPostoffice: 在Postoffice中的资源编号
		nMRoleVerifyIdenti:		在当前网关，和套接字值对应的唯一标志，用来认证是否和原先一致，可以暂时不用。
	*/
	int nIdentiInPostoffice;
	int nInPostSocket;
	int nResIdentiInPostoffice;
	//int nMRoleVerifyIdenti;

public:
	MsgUpdateTest1()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;
		
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgUpdateTest1)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};

class MsgTest2:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=2,
		DoAction=1
	};
	int i;

public:
	MsgTest2()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;
		
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgTest2)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};

class MsgTest3:public MsgBaseHead
{
public:
	enum
	{
		OrderAction=2,
		DoAction=2
	};

	int nMoney;

public:
	MsgTest3()
	{
		__nActionOrder = OrderAction;
		__nActionDo = DoAction;

		nRoutePriority = 1;
		
		nSizeOfMsg = sizeof(*this);	
		STATIC_ASSERT(sizeof(MsgTest3)<name_msg_protocol::SOCKET_BUFF_SIZE);
	}
};

