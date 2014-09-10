extern "C"
{
#include<lua.h>
#include<lauxlib.h>
#include<lualib.h>
}

#include<iostream>
using std::cout;
using std::endl;

static int sayHi(lua_State *L)
{
	double arg0 = lua_tonumber(L, 1);		//参数从lua层传过来从左往右
	double arg1 = luaL_checknumber(L, 2);	//一个一个压入栈的，所以栈底是第一个参数（也即是L[1]）
	cout<<arg0<<","<<arg1<<" hello lua -- from cpp"<<endl;
	const char *res = "xyb";
	lua_pushstring(L, "xyb");	//我擦这样都能传参？！！
	return 1;
}

int main()
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	lua_register(L, "sayHi", sayHi);
	luaL_loadfile(L, "sayHi.lua");
	lua_call(L, 0, 0);	//priming run，不需要任何传入参数和返回值，只是为了run一遍，让函数被定义
	lua_close(L);

	return 0;
}