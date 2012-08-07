#pragma once

extern "C"
{
	#include "../src/lua.h"
	#include "../src/lauxlib.h"
	#include "CQuestType1.h"
	#include "CQuestType2.h"
}
/*
	�ڴ�ӿ��ɳ������,���Դ�����Ͳ��ṩdelete
	param1:��������
*/
int CreateQuest(lua_State *L);

/*
	����ӿ�
	param1:����
	param2..x:����
*/
/*
	��������ӿ�
*/
//��ȡ��������
int GetCommonQuestType(lua_State *L);
int SetCommonQuestType(lua_State *L);

/*
	���Ե�����ӿ�
	��ͬCQuestType��������Ӧ�ýӿ�
*/
//QuestType1�Ľӿ�
int GetQuestType1(lua_State *L);
int SetQuestType1(lua_State *L);


//QuestType2�Ľӿ�
int GetQuestType2(lua_State *L);
int SetQuestType2(lua_State *L);



/*
	��ע��
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