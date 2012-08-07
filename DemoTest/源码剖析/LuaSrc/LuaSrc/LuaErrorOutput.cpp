#include <stdio.h>
#include "LuaErrorOutput.h"

void PrintLuaError(lua_State *L, int nErrNum)
{
	if (nErrNum==0)  
	{  
		return;  
	}  
	const char* error;  
	char sErrorType[256]={0};  
	switch(nErrNum)  
	{  
	case LUA_ERRSYNTAX://编译时错误  
		/*const char *buf = "mylib.myfun()2222";类似这行语句可以引起编译时错误*/  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","syntax error during pre-compilation");  
		break;  
	case LUA_ERRMEM://内存错误  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","memory allocation error");  
		break;  
	case LUA_ERRRUN://运行时错误  
		/*const char *buf = "my222lib.myfun()";类似这行语句可以引起运行时错误，my222lib实际上不存在这样的库，返回的值是nil*/  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","a runtime error");  
		break;  
	case LUA_YIELD://线程被挂起错误  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","Thread has Suspended");  
		break;  
	case LUA_ERRERR://在进行错误处理时发生错误  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","error while running the error handler function");  
		break;  
	default:  
		break;  
	}  
	error = lua_tostring(L, -1);//打印错误结果  
	printf("%s:%s",sErrorType,error);  
	lua_pop(L, 1);   	
}

void PrintLuaDebug(lua_State *L)
{
	lua_Debug LuaDebug;

	int nLevel=0;
	while( lua_getstack(L, nLevel, &LuaDebug) )
	{
		nLevel++;
	}

	if( !nLevel )
	{
		return;
	}

	//lua_getstack(L, level, &debug);
	//lua_getinfo(L, "Sln", &debug);

	lua_getstack(L, nLevel, &LuaDebug);
	lua_getinfo(L, "Sln", &LuaDebug);

	const char* pErr=lua_tostring(L, -1);
	lua_pop(L, 1);

	char Buff[256]={0};
	sprintf(Buff, "%s, line:%d, name:%s, what:%s\n",
		LuaDebug.short_src, LuaDebug.currentline, LuaDebug.namewhat, LuaDebug.name);

	printf("PrintLuaDebug:%s\n", Buff);
	//msg << " [" << err << "]";
	//lua_pushstring(L, msg.str().c_str());
	//return 1;
}