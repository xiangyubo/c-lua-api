extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

#include<stdio.h>

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L, "callfuncscript.lua");
	lua_pcall(L, 0, 0, 0);	//这一次是priming run，必须有！ 
	lua_getglobal(L, "tellme");
	printf("In C, calling Lua\n");
	lua_pcall(L, 0, 0, 0);	//这一次是真正运行函数	
	printf("Back in C again\n");

	lua_getglobal(L, "square");
	lua_pushnumber(L, 6);
	lua_pcall(L, 1, 1, 0);
	int mynumber = lua_tonumber(L, -1);
	printf("returnede number=%d\n", mynumber);
	lua_close(L);
	return 0;
}