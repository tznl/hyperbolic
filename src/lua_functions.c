#include "raylib.h"
#include "include/define.h"
#include "include/scene.h"
#include <stdio.h>
/*needed to create a directory*/
#include <sys/stat.h>
#include <sys/types.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

int load_config(){
	/* OPEN LUA */
	L = luaL_newstate();
	luaL_openlibs(L);

	/* LOAD CONFIG FILE (as chunk to run later) */
	if (luaL_loadfile(L, "config.lua")) {
/* stack: chunk */
		printf("Error loading config file: %s\n", lua_tostring(L, -1));
		lua_close(L);
		return 1;
	}

	/* SETUP ENVIRONMENT */
	lua_newtable(L); // environment table for our chunk
/* stack: chunk, environment */
	lua_newtable(L); // metatable for our environment
/* stack: chunk, environment, metatable */
	lua_pushstring(L, "__index");
/* stack: chunk, environment, metatable, "__index" */
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
/* stack: chunk, environment, metatable, "__index", GLOBALS */
	lua_rawset(L, -3); // metatable.__index = GLOBALS
/* stack: chunk, environment, metatable */
	lua_setmetatable(L, -2); // set environment's metatable
/* stack: chunk, environment */

	/* SAVE ENVIRONMENT */
	lua_pushstring(L, RIDX_CONFIG);
/* stack: chunk, environment, "config" */
	lua_pushvalue(L, -2);
/* stack: chunk, environment, "config", environment */
	lua_rawset(L, LUA_REGISTRYINDEX); // REGISTRY.config = environment
/* stack: chunk, environment */

	/* RUN CHUNK */
	lua_setupvalue(L, -2, 1); // set chunk's environment
/* stack: chunk */
	if (lua_pcall(L, 0, 0, 0)) { // run the chunk
/* stack: (none) */
		printf("Error running config file: %s\n", lua_tostring(L, -1));
		lua_close(L);
		return 1;
	}

	/* PRINT ENVIRONMENT */
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
/* stack: GLOBALS */
	lua_pushstring(L, RIDX_CONFIG);
/* stack: GLOBALS, "config" */
	lua_rawget(L, LUA_REGISTRYINDEX);
/* stack: GLOBALS, environment */
	lua_pushnil(L);
/* stack: GLOBALS, environment, nil */
	while (lua_next(L, -2)) {
		if(lua_isstring(L, -2)){
/* stack: GLOBALS, environment, key, value */
			lua_pushstring(L, "tostring");
/* stack: GLOBALS, environment, key, value, "tostring" */
			lua_gettable(L, -5);
/* stack: GLOBALS, environment, key, value, function */
			lua_insert(L, -2);
/* stack: GLOBALS, environment, key, function, value */
			lua_call(L, 1, 1); // tostring(value)
/* stack: GLOBALS, environment, key, string */
			printf("%s = %s\n", 
				lua_tostring(L, -2), lua_tostring(L, -1));
		}
		lua_pop(L, 1);
/* stack: GLOBALS, environment, key */
	}
	lua_pop(L, 2);
/* stack: none */

	/* SUCCESS */
	return 0;
}

int get_letterbox(bool *result){
	lua_pushstring(L, RIDX_CONFIG);
	/* stack: "config" */
	lua_rawget(L, LUA_REGISTRYINDEX);
	lua_pushstring(L, "letterboxing");
	/* stack: environment, "letterboxing" */
	lua_rawget(L, -2); // get value of environment.letterboxing
	/* stack: environment, value */
	if (!lua_isboolean(L, -1)) {
		/* stack: environment, value */
		printf("\033[0;31mERROR: letterboxing is defined as "
			"%s as opposed to the mandatory bool\n",
			lua_typename(L, lua_type(L, -1)));
		return 1;

	}
	*result = lua_toboolean(L, -1);
	/* stack: environment, value */
	lua_pop(L, 2);
	/* stack: (none) */

	/* SUCCESS */
	return 0;
}
