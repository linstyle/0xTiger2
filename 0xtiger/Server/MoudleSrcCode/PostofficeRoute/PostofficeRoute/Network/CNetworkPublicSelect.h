#pragma once
#include "0x_Network.h"

//
//对公共库CNetworkPublic的一个扩展，select模型
class CNetworkPublicSelect:public CCommonSocket
{
public:
	fd_set SetWrite;
	fd_set SetRead;

private:

public:	
	CNetworkPublicSelect();
	
	//GetConnectSum
	//from SetRead.fd_count
	int GetConnectSum();
	int AddToReadSet(int nSocket);
	void EraseFromReadSet(int nSocket);

private:

};