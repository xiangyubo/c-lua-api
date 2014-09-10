extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

#include<iostream>
using std::cout;
using std::endl;

int get_attr(lua_State *&L, int index, const char *key)
{
	lua_pushstring(L, key);
	lua_gettable(L, index);
	int result = (int)(lua_tonumber(L, -1) * 255);
	lua_pop(L, 1);
	return result;
}

void set_attr(lua_State *&L, int index, const char *key, double value)
{
	lua_pushstring(L, key);
	lua_pushnumber(L, value);
	lua_settable(L, index);
}

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	
	if(luaL_loadfile(L, "conf.lua") || lua_pcall(L, 0,0,0))	//返回非零值时表示有错误
	{
		cout<<"error occered:"<<endl;
		const char *err = lua_tostring(L, -1);
		cout<<err<<endl;
		lua_pop(L, lua_gettop(L));
		lua_close(L);
		exit(-1);
	}

	lua_getglobal(L, "back");
	int red = get_attr(L, lua_gettop(L), "r");
	int green = get_attr(L, lua_gettop(L), "g");
	int blue = get_attr(L, lua_gettop(L), "b");

	cout<<"red: "<<red<<endl;
	cout<<"green: "<<green<<endl;
	cout<<"blue: "<<blue<<endl;

	lua_newtable(L);
	cout<<"len of L: "<<lua_gettop(L)<<endl;
	set_attr(L, lua_gettop(L), "oo", 0.5);
	lua_setglobal(L, "xx");

	lua_getglobal(L, "xx");
	int oo = get_attr(L, lua_gettop(L), "oo");

	cout<<"oo: "<<oo<<endl;

	cout<<"len of L: "<<lua_gettop(L)<<endl;
	lua_close(L);
}