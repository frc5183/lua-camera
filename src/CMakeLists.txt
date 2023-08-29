cmake_minimum_required (VERSION 3.13)

### Basic compilation settings
set (CMAKE_POSITION_INDEPENDENT_CODE TRUE)

include_directories (
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_BINARY_DIR}
)

### Compiler-specific flags
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	add_compile_options ("-fvisibility=hidden")
	add_link_options ("-fvisibility=hidden")
endif ()
find_package (LuaJIT)
	if (LUAJIT_FOUND)
		set(LUA_INCLUDE_DIR ${LUAJIT_INCLUDE_DIR})
		set(LUA_LIBRARIES ${LUAJIT_LIBRARY})
	else ()
		find_package (Lua 5.1 REQUIRED)
	endif ()

	include_directories (${LUA_INCLUDE_DIR})

add_library (camera MODULE
	lua/main.cpp
)

add_library (camera-android STATIC EXCLUDE_FROM_ALL
	android/Android.cpp
)
target_link_libraries(camera ${LUA_LIBRARIES})
target_link_libraries(camera camera-android)
message(STATUS "Ensure to add the Java files to your project too!")
install(TARGETS camera DESTINATION .)
