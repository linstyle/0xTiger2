#pragma once

extern "C"
{
	#include "../src/lua.h"
	#include "../src/lauxlib.h"
	#include "CQuestType1.h"
	#include "CQuestType2.h"
}
/*
	内存接口由程序管理,测试代码里就不提供delete
	param1:任务类型
*/
int CreateQuest(lua_State *L);

/*
	任务接口
	param1:对象
	param2..x:参数
*/
/*
	公共任务接口
*/
//获取任务类型
int GetCommonQuestType(lua_State *L);
int SetCommonQuestType(lua_State *L);

/*
	各自的任务接口
	不同CQuestType，导出的应用接口
*/
//QuestType1的接口
int GetQuestType1(lua_State *L);
int SetQuestType1(lua_State *L);


//QuestType2的接口
int GetQuestType2(lua_State *L);
int SetQuestType2(lua_State *L);



/*
	库注册
*/
static const luaL_Reg QuestLibL[]=
{
	{"CreateQuest", CreateQuest},
	{NULL, NULL}
};

static const luaL_Reg QuestLibF[]=
{
	//{"CreateQuest", CreateQuest},
	{"GetCommonQuestType", GetCommonQuestType},
	//{"GetQuestType1", GetQuestType1},
	//{"GetQuestType2", GetQuestType2},

	//{"SetCommonQuestType", SetCommonQuestType},
	//{"SetQuestType1", SetQuestType1},
	//{"SetQuestType2", SetQuestType2},
	{NULL, NULL}
};

LUALIB_API int luaopen_quest (lua_State *L);