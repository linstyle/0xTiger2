/*
	@lindp lin_style@foxmail.com   
	@2012/3/12
	ѭ�����������ȡ����
*/

#pragma once
#include "Singleton.h"

class CLogicDriver:public Singleton<CLogicDriver>
{
public:
	void Loop();

private:
	void LoopGetPacketStream();

public:

private:

};

#define  g_LogicDriver CLogicDriver::getSingleton()