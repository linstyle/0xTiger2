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
	case LUA_ERRSYNTAX://����ʱ����  
		/*const char *buf = "mylib.myfun()2222";���������������������ʱ����*/  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","syntax error during pre-compilation");  
		break;  
	case LUA_ERRMEM://�ڴ����  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","memory allocation error");  
		break;  
	case LUA_ERRRUN://����ʱ����  
		/*const char *buf = "my222lib.myfun()";����������������������ʱ����my222libʵ���ϲ����������Ŀ⣬���ص�ֵ��nil*/  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","a runtime error");  
		break;  
	case LUA_YIELD://�̱߳��������  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","Thread has Suspended");  
		break;  
	case LUA_ERRERR://�ڽ��д�����ʱ��������  
		sprintf_s(sErrorType,sizeof(sErrorType),"%s","error while running the error handler function");  
		break;  
	default:  
		break;  
	}  
	error = lua_tostring(L, -1);//��ӡ������  
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