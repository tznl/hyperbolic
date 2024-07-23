#include "raylib.h"

#include <stdio.h>
#include <sqlite3.h>

#include "include/define.h"
#include "include/scene.h"
#include "include/codepoints.h"

#define RIDX_CONFIG "config"

void draw_scene(int *code);
static void draw_render(RenderTexture2D render);

int main(void)
{
	if(config_retrieve() == 1) {
		return 1;
	}

	screen_width = 640;
	screen_height = 480;

	InitWindow(screen_width, screen_height, "hyperbolic");
	InitAudioDevice();
	SetTargetFPS(60);

	assign_default();
	current_res = &default_res;

	RenderTexture2D render = LoadRenderTexture(screen_width, screen_height);
//	SetTextureFilter(render.texture, TEXTURE_FILTER_BILINEAR);

//	screen_load_font();

	while(!exit_window) {

		BeginTextureMode(render);
		draw_scene(&current_scene);
		EndTextureMode();

		BeginDrawing();

		draw_render(render);

		EndDrawing();

		if (WindowShouldClose()) 
			exit_window = true;
	}
	unload_current_res();
	config_free(&config_current); 
	CloseAudioDevice();
	CloseWindow();

	return 0;
}

static void draw_render(RenderTexture2D render)
{
	if (!config_current.letterbox) {
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
