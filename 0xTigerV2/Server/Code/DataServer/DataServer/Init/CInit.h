/*  作者：		林东平                                                              
	创建时间：	2010/12/25                                                       
    功能说明：  单例生命周期管理
*/

#pragma once
#include "Singleton.h"
#include "CCommonLibInit.h"
#include "CInitPackets.h"

#include "../Logic/Role/CRoleAllocator.h"
#include "../Config/CConfigRead.h"
#include "CMGuid.h"


class CInit:public Singleton<CInit>
{
public:
	CInit();
	~CInit();

	/*
		单例管理器
	*/
	void InitCommonLib();
	void DeleteCommonLib();

	/*
		配置文件
	*/
	void InitConfigRead();
	void DeleteConfigRead();
	/*
		guid
	*/
	void InitGUID();
	unsigned int SpliteConfigGuid(DATA_SERVER_GUID *pGateWayGuid, GAME_IDENTI_TYPE IdentiType);
	void DeleteGUID();
	/*
		日志
	*/
	void InitLog();
	void DeleteLog();

	/*
		协议包
	*/
	void InitPackets();
	void DeletePackets();

	/*
		人物分配管理池
	*/
	void InitRoleAllocator();
	void DeleteRoleAllocator();

private:

public:

private:

};