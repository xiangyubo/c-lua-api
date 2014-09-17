#define LUA_BUILD_AS_DLL
#define LUA_LIB

#ifdef __cplusplus
extern "C"
{
#endif

#include<lua.h>
#include<lualib.h>
#include<lauxlib.h>

typedef struct Array
{
	size_t size;
	double values[1];
}Array;

static int newarray(lua_State *L)
{
	size_t size = luaL_checkint(L, 1);
	size_t bytes = sizeof(Array) + sizeof(double) * (size - 1);
	Array * a = (Array*)lua_newuserdata(L, bytes);
	a->size = size;
	return 1;
}


static int setarray(lua_State *L)
{
	Array *a = (Array*)lua_touserdata(L, 1);
	size_t index = lua_tointeger(L, 2);
	double val = lua_tonumber(L, 3);

	luaL_argcheck(L, a != NULL, 1, "`array' expected");
	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

	a->values[index - 1] = val;

	return 0;
}

static int getarray(lua_State *L)
{
	Array *a = (Array*)lua_touserdata(L, 1);
	size_t index = lua_tointeger(L, 2);

	luaL_argcheck(L, a != NULL, 1, "`array' expected");
	luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");

	lua_pushnumber(L, a->values[index - 1]);

	return 1;
}

static int getsize(lua_State *L)
{
	Array *a = (Array*)lua_touserdata(L, 1);
	
	luaL_argcheck(L, a != NULL, 1, "`array' expected");

	lua_pushinteger(L, a->size);

	return 1;
}

static const luaL_reg mylibs[] = 
{
	{"new", newarray},
	{"geti", getarray},
	{"seti", setarray},
	{"size", getsize},
	{NULL, NULL}
};

LUALIB_API int luaopen_array(lua_State *L)
{
	luaL_register(L, "array", mylibs); 
	return 1;
}

#ifdef __cplusplus
}
#endif