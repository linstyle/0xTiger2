#pragma once
#include "0x_Network.h"

//
//�Թ�����CNetworkPublic��һ����չ��selectģ��
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