#define LUA_LIB
#define LUA_BUILD_AS_DLL

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
		int len = luaL_checkint(L, 1);
		size_t bytes = sizeof(Array) + (len - 1) * sizeof(double);
		Array *a = (Array*)lua_newuserdata(L, bytes);

		luaL_getmetatable(L, "type-array");
		lua_setmetatable(L, -2);

		a->size = len;
		return 1;
	}

	static Array* check_array(lua_State *L)
	{
		Array *res = (Array*) luaL_checkudata(L, 1, "type-array");
		luaL_argcheck(L, res != NULL, 1, "`array' expected");
		return res;
	}

	static double* getelem(lua_State *L)
	{
		Array *a = check_array(L);
		size_t index = luaL_checkint(L, 2);
		luaL_argcheck(L, 1 <= index && index <= a->size, 2, "index out of range");
		return &a->values[index - 1];
	}

	static int setarray(lua_State *L)
	{
		double val = lua_tonumber(L, 3);
		*getelem(L) = val;
		return 0;
	}

	static int getarray(lua_State *L)
	{
		lua_pushnumber(L, *getelem(L));
		return 1;
	}

	static int getsize(lua_State *L)
	{
		Array *a = check_array(L);
		lua_pushinteger(L, a->size);
		return 1;
	}

	static const luaL_reg mylibs[] = 
	{
		{"new", newarray},
		{NULL, NULL}
	};

	static const luaL_reg funcs[] = 
	{
		{"geti", getarray},
		{"seti", setarray},
		{"size", getsize},
		{NULL, NULL}
	};

	LUALIB_API int luaopen_array(lua_State *L)
	{
		luaL_newmetatable(L, "type-array");
		lua_pushfstring(L, "__index");
		lua_pushvalue(L, -2);
		lua_settable(L, -3);
		luaL_register(L, NULL, funcs);

		luaL_register(L, "array", mylibs); 
		return 1;
	}

#ifdef __cplusplus
}
#endif