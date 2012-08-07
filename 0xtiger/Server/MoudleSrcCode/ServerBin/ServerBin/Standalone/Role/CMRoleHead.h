#pragma once
#include "Algorithm/CListOfArray.h"
/*
	提供各个程序部件，一些资源所需要的额外信息
*/
namespace name_mrole_head
{
	const int IDENTI_NORMAL = 0;
	const int IDENTI_BIN = 1;
	const int IDENTI_OTHER = 2;

	const int RUN_STATE_DEAD  = -1;   //无效的死链接
	const int RUN_STATE_ENTER = 0;	  //刚连接上
	const int RUN_STATE_DOING = 1;	  //已经登陆，工作中
};

/*
	在邮局服务器上的记录信息
*/
struct IN_POSTOFFICE
{
	int nWherePostoffice;			//哪个网关
	int nSocket;					//该网关上的套接字值
	int nResIdenti;					//在该网关上的资源编号
};

/*
	在dpc服务器上的记录信息
*/
struct IN_DPC
{
	int nResIdenti;					//在DPC服务器上的资源编号
};

/*
	在CGlobalResMRole上的记录信息
*/
struct IN_GLOBALRES_MROLE
{
	int nResIdenti;					//在Global上的资源编号
};

/*
	在CMRoleManger,指针链表中的记录信息
*/
struct IN_CMROLEMANAGER
{
	int nResIdenti;
};

/*
	在哪个场景中信息
*/
struct IN_SCENE
{
	int nWhereIdenti;
};

class CMRoleHead
{
public:
	IN_DPC				InDpc;
	IN_POSTOFFICE		InPostoffice;
	IN_GLOBALRES_MROLE  InGlobalResMRole;
	IN_CMROLEMANAGER	InMRoleManager;
	IN_SCENE			InScene;

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