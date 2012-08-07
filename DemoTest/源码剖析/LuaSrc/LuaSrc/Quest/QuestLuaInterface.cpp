#include "QuestLuaInterface.h"


LUALIB_API int luaopen_quest (lua_State *L) {
	luaL_newmetatable(L, "Metatable.Quest");
	lua_pushvalue(L ,-1);
	lua_setfield(L, -2, "--index");

	//给元表
	luaL_register(L, NULL, QuestLibF);
	//创建函数单独导出
	luaL_register(L, "Quest", QuestLibL);
	//luaL_register(L, "Quest", QuestLibF);
	
	return 1;
}

int CreateQuest(lua_State *L)
{
	int nResult;
	CQuestType1 *pQuestType1;
	CQuestType2 *pQuestType2;

	nResult = luaL_checkint(L, 1);
	switch (nResult)
	{
	case 1:
		//pQuestType1 = new CQuestType1;
		//lua_pushlightuserdata(L, (void*)pQuestType1);
		pQuestType1 = (CQuestType1 *)lua_newuserdata(L, sizeof(CQuestType1));
		break;

	case 2:
		pQuestType2 = new CQuestType2;
		lua_pushlightuserdata(L, (void*)pQuestType2);
		break;

	default:
		printf("Err, CreateQuest:case default(%d)\n", nResult);
		return 0;
	}

	luaL_getmetatable(L, "Metatable.Quest");
	lua_setmetatable(L,-2);


	return 1;
}

int GetCommonQuestType(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestObjectBase *pQuestObjectBase = (CQuestObjectBase*)lua_touserdata(L, 1);

	int nType = pQuestObjectBase->GetType();

	lua_pushinteger(L, nType);
	return 1;
}

int SetCommonQuestType(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestObjectBase *pQuestObjectBase = (CQuestObjectBase*)lua_touserdata(L, 1);
	int nType = luaL_checkint(L,2);
	pQuestObjectBase->SetType(nType);

	return 0;
}

int GetQuestType1(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestType1 *pQuestType1 = (CQuestType1*)lua_touserdata(L, 1);
	int nType = pQuestType1->GetType1();

	lua_pushinteger(L, nType);	
	return 1;
}

int SetQuestType1(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestType1 *pQuestType1 = (CQuestType1*)lua_touserdata(L, 1);
	int nType1 = luaL_checkint(L,2);

	pQuestType1->SetType1(nType1);

	return 0;
}

int GetQuestType2(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestType2 *pQuestType2 = (CQuestType2*)lua_touserdata(L, 1);

	int nType = pQuestType2->GetType2();

	lua_pushinteger(L, nType);
	return 1;
}

int SetQuestType2(lua_State *L)
{
	luaL_checkudata(L, 1, "Metatable.Quest");
	CQuestType2 *pQuestType2 = (CQuestType2*)lua_touserdata(L, 1);
	int nType2 = luaL_checkint(L,2);

	pQuestType2->SetType2(nType2);

	return 0;
}