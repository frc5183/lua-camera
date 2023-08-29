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
extern "C"
{
static const struct luaL_Reg libs [] = {
        {"activate", w_activate},
        {"getPicture", w_getpicture},
        {NULL, NULL}
};
 int luaopen_camera(lua_State *L)
{
    luaL_register(L, "camera", libs);
    return 1;
}

}
