// LuaSrc.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//����һ��ָ��Lua��������ָ�롣
	L = lua_open();
	//��������Lua��
	luaL_openlibs(L);
	//�ҵ������
	luaopen_quest(L);
	/* register our function */  
	lua_register(L, "Average", Average);  

	//���ؽű�
	int error = luaL_dofile(L,"LuaCoroutine.lua");
	PrintLuaError(L,error);

	//�ر� �ͷ���Դ   
	lua_close(L);
	return 0;
}

