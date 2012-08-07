#pragma once
#include "0x_Exception.h"
#include "0x_Network.h"
/*
  һЩ��ͬ���ֶ��ϣ����ֲ���
  ��������ͻ��˷���ʹ�õ��ֶ�ǰ���"_"

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
		OrderAction=2,		//��ʾһ�����ද���ı�־
		DoAction=0			//��ʾ����ִ�еĶ���	
	};
	/*
		���nPort��nIP��Ϊ�㣬��ʾ��ȡʧ��
	*/
	int _nPort;
	unsigned long _nIP;
	char _strEncry[256];	//�ͻ���IP+�ͻ���PORT+�ʾַ�����IP+�ʾַ�����PORT+ʱ��

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

