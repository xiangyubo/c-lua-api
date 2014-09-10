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
	double arg0 = lua_tonumber(L, 1);		//������lua�㴫������������
	double arg1 = luaL_checknumber(L, 2);	//һ��һ��ѹ��ջ�ģ�����ջ���ǵ�һ��������Ҳ����L[1]��
	cout<<arg0<<","<<arg1<<" hello lua -- from cpp"<<endl;
	const char *res = "xyb";
	lua_pushstring(L, "xyb");	//�Ҳ��������ܴ��Σ�����
	return 1;
}

int main()
{
	lua_State *L = lua_open();
	luaL_openlibs(L);

	lua_register(L, "sayHi", sayHi);
	luaL_loadfile(L, "sayHi.lua");
	lua_call(L, 0, 0);	//priming run������Ҫ�κδ�������ͷ���ֵ��ֻ��Ϊ��runһ�飬�ú���������
	lua_close(L);

	return 0;
}