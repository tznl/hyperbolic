#include "raylib.h"
#include "include/define.h"
#include "include/scene.h"
#include <stdio.h>
/*needed to create a directory*/
#include <sys/stat.h>
#include <sys/types.h>

void scene_choose(int *code);

Texture2D menu1;
Font default_font;

int main(void)
{
	int current_scene = TITLE;

	screen_width = 640;
	screen_height = 480;

	InitWindow(screen_width, screen_height, "hyperbolic");
	InitAudioDevice();
	SetTargetFPS(60);

	RenderTexture2D render = LoadRenderTexture(screen_width, screen_height);
	menu1 		= LoadTexture("assets/default/testmenu.png");
	default_font 	= LoadFontEx(
		"assets/default/NotoSerifDisplay-Italic-VariableFont_wdth,wght.ttf",
		50,
		0,
		0);


	while(!WindowShouldClose()) {

		BeginTextureMode(render);
		scene_choose(&current_scene);
		EndTextureMode();

		BeginDrawing();

		float extra;

		if ((float)GetScreenWidth()/GetScreenHeight() > (float)screen_width/screen_height) {
			extra = GetScreenWidth() - GetScreenHeight() * 
				((float)screen_width / screen_height); // for example at 1920x1080, 1080 * 4:3 = 1440, then 1920 - 1440 = 480 extra pixels horizontally
			DrawTexturePro(
				render.texture, 
				(Rectangle) { 0, 0, 
					(float)render.texture.width, 
					(float)-render.texture.height }, 
				(Rectangle) { extra/2 ,0 , 
					GetScreenWidth()-extra,
					GetScreenHeight()}, 
				(Vector2) { 0, 0 },
				0,
				WHITE);
		} else{
			extra = GetScreenHeight() - GetScreenWidth() * ((float)screen_height / screen_width); // for example at 1000x1000, 1000 * 3:4 = 750, then 1000 - 750 = 250 extra pixels vertically
			DrawTexturePro(
				render.texture, 
				(Rectangle) { 0, 0, 
					(float)render.texture.width, 
					(float)-render.texture.height }, 
				(Rectangle) { 0 ,extra/2 , 
					GetScreenWidth(),
					GetScreenHeight()-extra}, 
				(Vector2) { 0, 0 },
				0,
				WHITE);
//			draw_shit(0, extra/2, w, h-extra); // at 1000x1000 this would be 0, 125, 1000, 875
		}

		EndDrawing();
	}
	CloseAudioDevice();
        CloseWindow();

	return 0;
}

void scene_choose(int *code)
{
	switch (*code) {
	case TITLE:
		draw_main();
		break;
	case SETTINGS:
		break;
	case PLAY:
		break;
	}
}
