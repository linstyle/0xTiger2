#pragma once

#include "../CUserRouteNavi.h"

namespace name_mrole_head
{
	const int IDENTI_NORMAL = 0;
	const int IDENTI_BIN = 1;
	const int IDENTI_OTHER = 2;

	const int RUN_STATE_DEAD  = -1;    //无效的死链接
	const int RUN_STATE_ENTER = 0;	  //刚连接上
	const int RUN_STATE_DOING = 1;	  //已经登陆，工作中
};


class CMRoleHead
{
public:
	CUserRouteNavi  UserRouteNavi;

	unsigned long bActiveTime;
	
private:
	//
	//namespace name_mrole_head
	int __nMRoleLevel;
	int __nMRoleRunState;

public:
	CMRoleHead();

	bool Init();

	void SetMRoleLevel(int nLevel)
	{
		__nMRoleLevel = nLevel;
	}

	int GetMRoleLevel()
	{
		return __nMRoleLevel;
	}

	void SetMRoleRunState(int nState)
	{
		__nMRoleRunState = nState;
	}

	int GetMRoleRunState()
	{
		return __nMRoleRunState;
	}

private:

};