#pragma once

#include "../stdafx.h"


class CUserBridgeNet
{
public:
	/*
		发起响应对象的套接字信息
	*/
	int nSocket;
	sockaddr_in SenderAddr;

	/*
		参数需要的信息
		nInNetPoolRes: 在网络层的资源ID，和逻辑对象一一对应
		nInNetToSocket:要回应给某对象的套接字
	*/
	int nInNetPoolRes;
	int nInNetToSocket;

private:

public:

private:
};