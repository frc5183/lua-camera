extern "C" {
#include <lua.h>
#include <lauxlib.h>
}

#include <string>
#include <cstddef>
#include "../android/Android.h"

#include <android/log.h>
#define LOG(...) __android_log_print(ANDROID_LOG_VERBOSE, "LuaCamera", __VA_ARGS__);

Android android = Android();

static int w_getpicture(lua_State *L) {
    std::string str = android.getSnap();

    if (str.empty()) {
        lua_pushnil(L);
    } else {
        lua_pushstring(L, str.c_str());
    }

    return 1;
};

static int w_activate(lua_State *L) {
    android.activate();
    return 0;
};

extern "C" {
static const struct luaL_Reg libs [] = {
        {"activate", w_activate},
        {"getPicture", w_getpicture},
        {NULL, NULL}
};

int luaopen_camera(lua_State *L) {
    luaL_register(L, "camera", libs);
    return 1;
}
}
