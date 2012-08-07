/*
	@lindp lin_style@foxmail.com   
	@2012/2/17
	@�����װ����CNetDriver2.h��public�Ĳ���,�����������뿴CNetDriver2.hͷ�ļ�
*/
#pragma once
#include "CNetDriver2.h"

namespace net  
{
	bool AddSocketServer(const char* pName, const char* pListenIP, USHORT nListenPort);	
	bool AddClientSocket(const char* pConnectIP, USHORT nConnectPort);

	int GetPacketStream(char *pBuffer, int nBufferLen);
	int PutPacketStream(const char *pBuffer, int nBufferLen);

	bool NoticNetErr();
};