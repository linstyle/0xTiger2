/*  作者：		林东平                                                              
	创建时间：	2010/12/25                                                       
    功能说明：  初始化协议
*/
#pragma once
#include "Singleton.h"

#include "../Packets/Accept.h"
#include "../Packets/Exception.h"
#include "DemoPFileTrans.h"

class CInitPackets:public Singleton<CInitPackets>
{
public:
	CInitPackets();
	~CInitPackets();

	void InitPackets();
	void DeletePackets();

private:

public:

private:

};