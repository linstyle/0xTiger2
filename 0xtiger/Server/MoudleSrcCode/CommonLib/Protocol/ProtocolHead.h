#pragma once
#include <memory.h>
#include "ProtocolHead_Pack.h"
//#����С�����Ż�
class MsgBaseHead
{
public:	
	int nSizeOfMsg;		//�������ݰ��Ĵ�С������ͷ��
	int __nActionOrder;	
	int __nActionDo;
	
	/*
		nDoPriority
		ִ�����ȵȼ�,0-5,Խ�ͱ�ʾȨ��Խ��. (Ĭ��Ϊ3)
	*/
	int nDoPriority;

	/*
		nRoutePriority
		·��ת���ĵȼ�, ��Ҫ�ֶ�����
		0:·������ִ������(Ĭ��)
		1:binת������		
		2:dpcת������
		3:ת���ͻ���00000000
		4:��������������
		2010:�ر�
	*/
	int nRoutePriority;

	/*
		debug,�ֶ�
	*/
	int nInBinPoolRes;//��ʱΪ0

public:
	MsgBaseHead()
	{
		nDoPriority = 3;
		nRoutePriority = 0;

		nInBinPoolRes = 0;
	}
};

/*
	�������Ӻ��ɿͻ��������˽��з��͸��ʺ�
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

