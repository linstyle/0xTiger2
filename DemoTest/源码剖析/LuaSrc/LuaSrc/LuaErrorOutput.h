#pragma once
extern "C"
{
	#include "lua.h" 
}
void PrintLuaError(lua_State *L, int nErrNum);
void PrintLuaDebug(lua_State *L);