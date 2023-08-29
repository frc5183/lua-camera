extern "C"
{
#include <lua.h>
#include <lauxlib.h>
}
#include <string>
#include "../android/Android.h"
Android android;
static int w_getpicture(lua_State *L)
{
    lua_pushstring(L, android.getSnap().c_str());
    return 0;
};
static int w_activate(lua_State *L) {
    android.activate();
    return 0;
};
extern "C" int luaopen_camera(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, w_activate);
    lua_setfield(L, -2, "activate");
    lua_pushcfunction(L, w_getpicture);
    lua_setfield(L, -2, "getPicture");
    return 1;
}
