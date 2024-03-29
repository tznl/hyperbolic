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
	enum options { LETTERBOXING = 0, BACK };
	float option_horizontal_offset = screen_width/20;
	float option_size = 60;
	

	Color letterboxing_color;
	Color letterbox_on;
	Color letterbox_off;

	Color back_color;

	DrawTexture(menu1, 0 , 0, WHITE);                                

	switch (selected) {
		case LETTERBOXING:
			letterboxing_color = YELLOW;
			back_color = WHITE;
			letterbox_on = WHITE;
			letterbox_off = WHITE;
			break;
		case BACK:
			letterboxing_color = WHITE;
			back_color = YELLOW;
			letterbox_on = WHITE;
			letterbox_off = WHITE;
			break;
	}

	DrawTextEx(default_font, "letterboxing",                           
		(Vector2){option_horizontal_offset, screen_height*0.60}, 
		option_size, 5, letterboxing_color);
	DrawTextEx(default_font, "on",                           
		(Vector2){screen_width/1.50, screen_height*0.60}, 
		option_size, 5, letterbox_on);
	DrawTextEx(default_font, "off",                           
		(Vector2){screen_width/1.25, screen_height*0.60}, 
		option_size, 5, letterbox_off);

	DrawTextEx(default_font, "back",                           
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
		selected_setting = 1;
		break;
	case 1:
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
