#pragma once

#include "CUserBridgeNet.h"
#include "CUserBridgeLogic.h"

class CUserBridge
{
public:
	//
	//����ص�ID
	CCommonObjectIdenti CommObjectIdenti;

	CUserBridgeLogic *pUserBridgeLogic;
	CUserBridgeNet   *pUserBridgeNet;

private:

public:

private:
};