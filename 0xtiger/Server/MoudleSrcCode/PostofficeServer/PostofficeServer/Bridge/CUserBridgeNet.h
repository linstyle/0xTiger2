#pragma once

#include "../stdafx.h"


class CUserBridgeNet
{
public:
	/*
		������Ӧ������׽�����Ϣ
	*/
	int nSocket;
	sockaddr_in SenderAddr;

	/*
		������Ҫ����Ϣ
		nInNetPoolRes: ����������ԴID�����߼�����һһ��Ӧ
		nInNetToSocket:Ҫ��Ӧ��ĳ������׽���
	*/
	int nInNetPoolRes;
	int nInNetToSocket;

private:

public:

private:
};