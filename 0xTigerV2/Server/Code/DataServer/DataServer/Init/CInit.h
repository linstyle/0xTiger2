/*  ���ߣ�		�ֶ�ƽ                                                              
	����ʱ�䣺	2010/12/25                                                       
    ����˵����  �����������ڹ���
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
		����������
	*/
	void InitCommonLib();
	void DeleteCommonLib();

	/*
		�����ļ�
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
		��־
	*/
	void InitLog();
	void DeleteLog();

	/*
		Э���
	*/
	void InitPackets();
	void DeletePackets();

	/*
		�����������
	*/
	void InitRoleAllocator();
	void DeleteRoleAllocator();

private:

public:

private:

};