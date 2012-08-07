========================================================================
    控制台应用程序：LuaSrc 项目概述
========================================================================

应用程序向导已为您创建了此 LuaSrc 应用程序。

本文件概要介绍组成 LuaSrc 应用程序的
的每个文件的内容。


LuaSrc.vcproj
    这是使用应用程序向导生成的 VC++ 项目的主项目文件，
    其中包含生成该文件的 Visual C++ 的版本信息，以及有关使用应用程序向导选择的平台、配置和项目功能的信息。

LuaSrc.cpp
    这是主应用程序源文件。

/////////////////////////////////////////////////////////////////////////////
其他标准文件：

StdAfx.h, StdAfx.cpp
    这些文件用于生成名为 LuaSrc.pch 的预编译头 (PCH) 文件和名为 StdAfx.obj 的预编译类型文件。

/////////////////////////////////////////////////////////////////////////////
其他注释：

应用程序向导使用“TODO:”注释来指示应添加或自定义的源代码部分。

/////////////////////////////////////////////////////////////////////////////


Recommended reading order: 

    * lmathlib.c, lstrlib.c: get familiar with the external C API. Don't bother with the 
    pattern matcher though. Just the easy functions. 
    * lapi.c: Check how the API is implemented internally. Only skim this to get a feeling 
    for the code. Cross-reference to lua.h and luaconf.h as needed. 
    * lobject.h: tagged values and object representation. skim through this first. you'll 
    want to keep a window with this file open all the time. 
    * lstate.h: state objects. ditto. 
    * lopcodes.h: bytecode instruction format and opcode definitions. easy. 
    * lvm.c: scroll down to luaV_execute, the main interpreter loop. see how all of the 
    instructions are implemented. skip the details for now. reread later. 
    * ldo.c: calls, stacks, exceptions, coroutines. tough read. 
    * lstring.c: string interning. cute, huh? 
    * ltable.c: hash tables and arrays. tricky code. 
    * ltm.c: metamethod handling, reread all of lvm.c now. 
    * You may want to reread lapi.c now. 
    * ldebug.c: surprise waiting for you. abstract interpretation is used to find object 
    names for tracebacks. does bytecode verification, too. 
    * lparser.c, lcode.c: recursive descent parser, targetting a register-based VM. start 
    from chunk() and work your way through. read the expression parser and the code g
    enerator parts last. 
    * lgc.c: incremental garbage collector. take your time. 
    * Read all the other files as you see references to them. Don't let your stack get too 
    deep though. 

If you're done before X-Mas and understood all of it, you're good. The information density 
of the code is rather high. 

 
二、C/C++对Lua的调用　以主 lua对C/C++的调用
 
 
extern "C"{
#include "../Lua5_1_4/Lua_Src_514/lua.h" 
#include "../Lua5_1_4/Lua_Src_514/lualib.h"
#include "../Lua5_1_4/Lua_Src_514/lauxlib.h"
}
lua_State  * L;                    //lua的全局对象
int luaadd ( int x, int y )
{
    int sum;
    //函数名
    lua_getglobal(L, "add");　
    //第一个参数压栈
    lua_pushnumber(L, x);　 /
    //第二个参数压栈
    lua_pushnumber(L, y);
    //调用函数
    lua_call(L, 2, 1);
    //得到返回值
    sum = (int)lua_tonumber(L, -1);
    lua_pop(L, 1);
    return sum;
}
 
static int average(lua_State *L)
{
       int n = lua_gettop(L);            //lua_gettop()的作用是返回栈顶元素的序号.
       double sum = 0;
       int i;
       for (i = 1; i <= n; i++)
       {
              sum += lua_tonumber(L, i);
       }
       lua_pushnumber(L, sum / n);
       lua_pushnumber(L, sum);// 然后偶们用lua_pushnumber()把平均值和总和push到栈中
       return 2;//最后, 偶们返回2, 表示有两个返回值
}
 
int main ( int argc, char *argv[] )
{
    int sum;
    //创建一个指向Lua解释器的指针。
    L = lua_open();
    //函数加载Lua库
    luaL_openlibs(L);
    //加载脚本
    int error = luaL_dofile(L,"add.lua");
    //调用函数
    sum = luaadd( 10, 11);
    // print the result
    printf( "The sum is %d\n", sum );
    //关闭 释放资源   
    lua_close(L);
    return 0;
}
 
Add.lua的编写
function add(x, y)
avg,sum=average(10,20)
return sum
end;
 
lua_state *L;
lua_open();
lua_openLibs(L);
luaL_doFile(L, “filename”);
lua_getgloble(L,”functionname”)
lua_pushnumber(L, 1);
lua_call(L,输入参数个数,输出参数);
lua_tonumber(L, -1);得到第一个返回值
lua_pop(L,1);
 
lua_gettop(Ｌ);返回参数个数