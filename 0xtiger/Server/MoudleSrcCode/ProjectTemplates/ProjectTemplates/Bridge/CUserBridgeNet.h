#pragma once

#include "../stdafx.h"
#include "Algorithm/CCommonObjectIdenti.h"
//
//因为PlayClient和RouteClient的缘故(两者服务对象不一样)，该结构的若干信息有所冗余.
class CUserBridgeNet
{
public:
	//
	//客户端的套接字信息
	int nSocket;
	sockaddr_in SenderAddr;
private:

public:

private:
};