#define LUA_BUILD_AS_DLL
#define LUA_LIB

#ifdef __cplusplus
extern "C"
{
#endif

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

#ifdef __cplusplus
}
#endif

const char *map[] = 
{
	"nil",
	"boolean",
	"light-user-data",
	"number",
	"string",
	"table",
	"function",
	"user-data",
	"trhead"
};

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

static int my_add(lua_State *L)
{
    double x = lua_tonumber(L,1);
    double y = lua_tonumber(L,2);
	double sum = x + y;
    lua_pushnumber(L, sum);
    return 1;
}

static int print_t(lua_State *L)
{
	if(lua_istable(L, -1) == false)
	{
		printf("Error occered! Param is not a table!\n");
		return -1;
	}
	lua_pushnil(L);
	const char* k, *v;
	while(lua_next(L, -2) != 0)
	{
		v = lua_isstring(L, -1) == 0 ? lua_tostring(L, -1) : map[lua_type(L, -1)];
		lua_pop(L, 1);
		k = lua_isstring(L, -1) == 0 ? lua_tostring(L, -1) : map[lua_type(L, -1)];
		printf("%s ===> %s\n", k, v);
	}
	return 0;
}

static const luaL_reg mylibs[] = 
{
	{"print_t", print_t},
	{"add", my_add},
	{NULL, NULL}
};

extern "C" LUALIB_API int luaopen_mylib(lua_State *L)
{
	luaL_register(L, "mylib", mylibs);
	return 1;
}