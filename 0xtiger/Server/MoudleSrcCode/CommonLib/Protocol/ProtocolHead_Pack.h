#pragma once
#include "0x_Exception.h"
/*
	��������֮�䲿���Ĺ�����,��¼�˴�֮�����Դ��Ϣ
	����ͳһ��IN��ͷ��
*/

namespace name_protocol_pack
{
	const int PACK_BUFF_SIZE = 20;
}

class MsgPostHead
{
public:	
	int nInSocket;

private:

public:
	MsgPostHead()
	{
		STATIC_ASSERT( sizeof(MsgPostHead)< name_protocol_pack::PACK_BUFF_SIZE );
	}

private:

};


class MsgBinHead
{
public:

private:

public:
	MsgBinHead()
	{
		STATIC_ASSERT( sizeof(MsgBinHead)< name_protocol_pack::PACK_BUFF_SIZE );
	}

private:
 
};

