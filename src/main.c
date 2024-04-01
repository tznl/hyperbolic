#include "raylib.h"

#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "include/define.h"
#include "include/scene.h"
#include "include/lua_functions.h"

#define RIDX_CONFIG "config"

void draw_scene(int *code);
static void draw_render(RenderTexture2D render, bool letterbox);

Texture2D menu1;
Font default_font;

int main(void)
{
	if(load_config())
		return 1;
	if(get_letterbox(&letterbox))
		return 1;

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
		draw_scene(&current_scene);
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
				{0.0f, 0.0f, render.texture.width, -render.texture.height},
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
		extra = sh - sw / ratio;
		y = extra / 2.0f;
		sh -= extra;
		x = 0.0f;
	}
	DrawTexturePro(
		render.texture,
		(Rectangle)
			{0.0f, 0.0f, render.texture.width, -render.texture.height},
		(Rectangle)
			{x, y, sw, sh},
		(Vector2)
			{0, 0},
		0,
		WHITE);
}

void draw_scene(int *code)
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
