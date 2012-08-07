#pragma once

#include "Protocol/ProtocolHead.h"

namespace name_bpmsg_protocol
{
	/*
		����Ǳ���ִ���������в��䣬��ת��������������
	*/
	const int BP_ORADER_ACTION_MAX = 3;
};

/*
	�߼�������bin��½
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
		nLine: �ߵı��
		nBinIdenti: ���ڵ�ΨһID
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
	�߼�������dpc��½
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
	1.p->g,gȥdb��֤
	2.dbͨ���������������ݸ�g,ȫ�����ݸ�m
	3.m��һ����ʱ�����ｨ���ý�ɫ�����ҵȴ�g���ݵ���Դ����
	4.g���ظý�ɫ��Դ��š����ر�Ÿ�m
	5.m��ʱ�������������㣬���ý�ɫ��Դ��Ÿ�����
	6.��ʼͨѶ
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
//	�û���������
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
		nIdentiInPostoffice:	���ڵ���������
		nInPostSocket:	��Postoffice�е��׽�����Ϣ
		nResIdentiInPostoffice: ��Postoffice�е���Դ���
		nMRoleVerifyIdenti:		�ڵ�ǰ���أ����׽���ֵ��Ӧ��Ψһ��־��������֤�Ƿ��ԭ��һ�£�������ʱ���á�
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

