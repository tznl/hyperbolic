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

void scene_choose(int *code);
static void draw_render(RenderTexture2D render, bool letterbox);

Texture2D menu1;
Font default_font;

int main(void)
{
	#define CONFIG_ENVIRONMENT "config"


	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if (luaL_loadfile(L, "config.lua")) {
		printf("Error loading config file: %s\n", lua_tostring(L, -1));
		lua_close(L);
		return 1;
	}

	lua_newtable(L); // environment
	lua_newtable(L); // metatable
	lua_pushstring(L, "__index");
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
	lua_rawset(L, -3); // metatable.__index = GLOBALS
	lua_setmetatable(L, -2);

	lua_pushstring(L, CONFIG_ENVIRONMENT);
	lua_pushvalue(L, -2);
	lua_rawset(L, LUA_REGISTRYINDEX); // REGISTRY[CONFIG_ENVIRONMENT] = environment

	lua_setupvalue(L, -2, 1);

	if (lua_pcall(L, 0, 0, 0)) {
		printf("Error running config file: %s\n", lua_tostring(L, -1));
		lua_close(L);
		return 1;

	}

	lua_pushstring(L, CONFIG_ENVIRONMENT);
	lua_rawget(L, LUA_REGISTRYINDEX);
	
	lua_pushstring(L, "letterboxing");
	lua_rawget(L, -2);

	if (!lua_isboolean(L, -1)) {
		printf("\033[0;31mERROR: letterboxing is defined as "
			"%s as opposed to the mandatory bool\n",
			lua_typename(L, lua_type(L, -1)));
		return 1;

	}
	bool letterbox = lua_toboolean(L, -1);
	lua_pop(L, 2);

	lua_pushstring(L, CONFIG_ENVIRONMENT);
	lua_rawget(L, LUA_REGISTRYINDEX);

	lua_pushnil(L);
	while(lua_next(L, -2)) {
			printf("%s = ",lua_tostring(L,-2));
		if(lua_isstring(L,-1))
			printf("%s\n",lua_tostring(L,-1));
		else if(lua_isboolean(L,-1))
			printf("%s\n",lua_toboolean(L,-1) ? "true" : "false");
		else if(lua_isnumber(L,-1))
			printf("%f\n",lua_tonumber(L,-1));
		else
			printf("?\n");
		lua_pop(L, 1);
	}

	screen_width = 640;
	screen_height = 480;

	InitWindow(screen_width, screen_height, "hyperbolic");
	InitAudioDevice();
	SetTargetFPS(60);

	RenderTexture2D render = LoadRenderTexture(screen_width, screen_height);
	menu1 		= LoadTexture("assets/default/testmenu.png");
	default_font 	= LoadFontEx(
		"assets/default/"
			"NotoSerifDisplay-Italic-VariableFont_wdth,wght.ttf",
		50,
		0,
		0);
	SetTextureFilter(default_font.texture, TEXTURE_FILTER_BILINEAR);


	while(!exit_window) {

		BeginTextureMode(render);
		scene_choose(&current_scene);
		EndTextureMode();

		BeginDrawing();

		draw_render(render, letterbox);

		EndDrawing();

		if (WindowShouldClose()) exit_window = true;
	}
	CloseAudioDevice();
	CloseWindow();
	lua_close(L);

	return 0;
}

static void draw_render(RenderTexture2D render, bool letterbox)
{
	if (!letterbox) {
		DrawTexturePro(
			render.texture,
			(Rectangle)
				{0.0f,0.0f,render.texture.width,-render.texture.height},
			(Rectangle)
				{0, 0, GetScreenWidth(), GetScreenHeight()},
			(Vector2)
				{0, 0},
			0,
			WHITE);

		return;
	}

	float sw = GetScreenWidth();
	float sh = GetScreenHeight();
	float ratio = (float)render.texture.width / render.texture.height;
	float x;
	float y;
	float extra;

	if (sw / sh > ratio) {
		extra = sw - sh * ratio; 
		x = extra / 2.0f;
		sw -= extra;
		y = 0.0f;
	} else {
		extra = sh - sw  / ratio; 
		y = extra / 2.0f;
		sh -= extra;
		x = 0.0f;
	}
	DrawTexturePro(
		render.texture,
		(Rectangle)
			{0.0f,0.0f,render.texture.width,-render.texture.height},
		(Rectangle)
			{x,y,sw,sh},
		(Vector2)
			{0, 0},
		0,
		WHITE);
}

void scene_choose(int *code)
{
	switch (*code) {
	case TITLE:
		draw_main();
		break;
	case SETTINGS:
		draw_settings();
		break;
	case PLAY:
		break;
	}
}
