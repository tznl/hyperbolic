#include "../include/scene.h"
#include "../include/define.h"
#include "raylib.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h> 

void settings_execute(int *selected);
void letterbox_choose(void);

int selected_setting;

void draw_settings()
{
	enum options { FULLSCREEN = 0, LETTERBOX, BACK };
	float option_horizontal_offset = screen_width/20;
	float option_size = 60;


	Color fullscreen_color;
	Color fullscreen_on;
	Color fullscreen_off;

	Color letterboxing_color;
	Color letterbox_on;
	Color letterbox_off;

	Color back_color;

	DrawTexture(current_res->menu_background, 0 , 0, WHITE);				

	switch (selected) {
		case FULLSCREEN:
			fullscreen_color = YELLOW;
			fullscreen_on = WHITE;
			fullscreen_off = WHITE;

			letterboxing_color = WHITE;
			letterbox_on = WHITE;
			letterbox_off = WHITE;

			back_color = WHITE;
			break;
		case LETTERBOX:
			fullscreen_color = WHITE;
			fullscreen_on = WHITE;
			fullscreen_off = WHITE;

			letterboxing_color = YELLOW;
			letterbox_on = WHITE;
			letterbox_off = WHITE;

			back_color = WHITE;
			break;
		case BACK:
			fullscreen_color = WHITE;
			fullscreen_on = WHITE;
			fullscreen_off = WHITE;

			letterboxing_color = WHITE;
			letterbox_on = WHITE;
			letterbox_off = WHITE;

			back_color = YELLOW;
			break;
	}
	//
	if (config_buffer.fullscreen) {
		fullscreen_on	= YELLOW;
		fullscreen_off	= WHITE;
	} else {
		fullscreen_on	= WHITE;
		fullscreen_off	= YELLOW;

	}
	//
	if (config_buffer.letterbox) {
		letterbox_on	= YELLOW;
		letterbox_off	= WHITE;
	} else {
		letterbox_on	= WHITE;
		letterbox_off	= YELLOW;
	}

	DrawTextEx(current_res->font, "fullscreen",
		(Vector2){option_horizontal_offset, screen_height*0.45}, 
		option_size, 5, fullscreen_color);
	DrawTextEx(current_res->font, "on",
		(Vector2){screen_width/1.50, screen_height*0.45}, 
		option_size, 5, fullscreen_on);
	DrawTextEx(current_res->font, "off",
		(Vector2){screen_width/1.25, screen_height*0.45}, 
		option_size, 5, fullscreen_off);

	DrawTextEx(current_res->font, "letterboxing",
		(Vector2){option_horizontal_offset, screen_height*0.60}, 
		option_size, 5, letterboxing_color);
	DrawTextEx(current_res->font, "on",
		(Vector2){screen_width/1.50, screen_height*0.60}, 
		option_size, 5, letterbox_on);
	DrawTextEx(current_res->font, "off",
		(Vector2){screen_width/1.25, screen_height*0.60}, 
		option_size, 5, letterbox_off);

	DrawTextEx(current_res->font, "back",
		(Vector2){option_horizontal_offset, screen_height*0.75}, 
		option_size, 5, back_color);

	switch (selected_setting) {
		case 0: break;
		case 1: letterbox_choose(); 
	}
	
	if (IsKeyPressed(KEY_UP) && selected > 0) {
		selected-=1;
	} else if (IsKeyPressed(KEY_DOWN) && selected < BACK) {
		selected+=1;
	} else if (IsKeyPressed(KEY_Z)) {
		settings_execute(&selected);
	}
}

void settings_execute(int *selected)
{
	switch (*selected) {
	case 0:
		selected_setting = 0;
		break;
	case 1:
		selected_setting = 1;
		break;
	case 2:
		*selected = 0;
		current_scene = TITLE;
		break;
	}
}

void letterbox_choose(void)
{
/*	switch () {
	}
	if (IsKeyPressed(KEY_X)) {
	selected_setting = 0;
	}
*/
}
