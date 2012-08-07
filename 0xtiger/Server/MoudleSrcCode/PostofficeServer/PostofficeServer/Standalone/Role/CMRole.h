#pragma once
#include "CMRoleHead.h"
#include <stdio.h>
/*
	
	外部的信息(head):用户身份等级标志，时间，登陆情况，路由导航
	内部的信息:真正的游戏数据信息{ }

*/


class CMRole 
{
public:
	CMRoleHead MRoleHead;
	//
	//debug
	int Open();
	int Close();
	

private:


public:
	CMRole();

private:

};