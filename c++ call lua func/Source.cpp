extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include<iostream>
using std::cout;
using std::endl;

int main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);
	luaL_loadfile(L, "callfuncscript.lua");
	lua_pcall(L, 0, 0, 0);
	lua_getglobal(L, "tweaktable");
	lua_newtable(L);
	lua_pushliteral(L, "fname");                /* Push a key onto the stack, table now at -2 */
    lua_pushliteral(L, "Margie");               /* Push a value onto the stack, table now at -3 */
    lua_settable(L, -3);                        /* Take key and value, put into table at -3, */
                                                /*  then pop key and value so table again at -1 */

    lua_pushliteral(L, "lname");                /* Push a key onto the stack, table now at -2 */    
    lua_pushliteral(L, "Martinez");             /* Push a value onto the stack, table now at -3 */
    lua_settable(L, -3);                        /* Take key and value, put into table at -3, */
                                                /*  then pop key and value so table again at -1 */

	lua_call(L, 1, 1);
	lua_pushnil(L);
	const char *k, *v;
	while (lua_next(L, -2))
	{
		v = lua_tostring(L, -1);
		lua_pop(L, 1);
		k = lua_tostring(L, -1);
		cout<<"Fromc k => "<<k<<" v => "<<v<<endl;
	}
	lua_close(L);
	return 0;
}