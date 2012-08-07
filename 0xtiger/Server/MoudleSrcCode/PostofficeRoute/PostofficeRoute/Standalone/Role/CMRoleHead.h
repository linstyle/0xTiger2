#pragma once

/*
	head这个部分里包含了最基本的和内部维护的信息。比如内部状态表示，身份等级表示

*/
namespace name_mrole_head
{
	const int IDENTI_NORMAL = 0;
	const int IDENTI_BIN = 1;
	const int IDENTI_OTHER = 2;

	const int RUN_STATE_DEAD  = -1;    //无效的死链接
	const int RUN_STATE_ENTER = 0;	  //刚连接上
	const int RUN_STATE_DOING = 1;	  //已经登陆，工作中
};

/*
	在MRoleManager中的资源编号
*/
struct IN_CMROLEMANAGER
{
	int nResIdenti;
};


class CMRoleHead
{
public:
	IN_CMROLEMANAGER InMRoleManager;

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