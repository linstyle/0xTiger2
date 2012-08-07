// LuaSrc.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "LuaErrorOutput.h"
extern "C"
{
	#include "lua.h" 
	#include "lualib.h"
	#include "lauxlib.h"	
}
#include "Quest/QuestLuaInterface.h"

lua_State  * L;
static int Average(lua_State *L)  
{
	printf("C++.Average");
	int n = lua_gettop(L); 
	for (int i = 1; i <= n; i++)  
	{  
		printf("%d,", lua_tonumber(L, i));
	}  

	return 1000;
}

int _tmain(int argc, _TCHAR* argv[])
{
	//创建一个指向Lua解释器的指针。
	L = lua_open();
	//函数加载Lua库
	luaL_openlibs(L);
	//我的任务库
	luaopen_quest(L);
	/* register our function */  
	lua_register(L, "Average", Average);  

	//加载脚本
	int error = luaL_dofile(L,"LuaCoroutine.lua");
	PrintLuaError(L,error);

	//关闭 释放资源   
	lua_close(L);
	return 0;
}

