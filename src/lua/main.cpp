extern "C"
(
#include <lua.h>
#include <lauxlib.h>
)
#include "../android/Android.h"
Android android = new Android();
static void w_getpicture(lua_State *L)
{
    lua_pushstring(L, android::getSnap());
};
static void w_activate(lua_State *L) {
    android::activate();
};
extern "c" int CAMERA_DDLEXPORT luaopen_camera(lua_State *L)
{
    lua_newtable(L);
    lua_pushcfunction(L, w_active);
    lua_setfield(L, -2, "activate");
    lua_pushcfunction(L, w_getpicture);
    lua_setfield(L, -2, "getPicture");
}