#pragma once
#include "0x_Exception.h"
/*
	各服务器之间部件的公共体,记录彼此之间的资源信息
	命名统一以IN打头。
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

