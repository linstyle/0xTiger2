#pragma once

#include "CUserBridgeNet.h"
#include "CUserBridgeLogic.h"

class CUserBridge
{
public:
	//
	//¶ÔÏó³ØµÄID
	CCommonObjectIdenti CommObjectIdenti;

	CUserBridgeLogic *pUserBridgeLogic;
	CUserBridgeNet   *pUserBridgeNet;

private:

public:

private:
};