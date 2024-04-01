#include "raylib.h"
#include <stdio.h>

#include "../include/scene.h"
#include "../include/define.h"
#include "../include/scenemanager.h"

void main_execute(int *selected);

void draw_main()
{
	enum options { PLAY = 0, SETTINGS, QUIT };
	float option_horizontal_offset = screen_width/1.5;
	float option_size = 60;
	

	Color play_color;
	Color settings_color;
	Color quit_color;

	DrawTexture(menu1, 0 , 0, WHITE);                                

	switch (selected) {
		case PLAY:
			play_color = YELLOW;
			settings_color = WHITE;
			quit_color = WHITE;
			break;
		case SETTINGS:
			play_color = WHITE;
			settings_color = YELLOW;
			quit_color = WHITE;
			break;
		case QUIT:
			play_color = WHITE;
			settings_color = WHITE;
			quit_color = YELLOW;
			break;
	}

	DrawTextEx(default_font, "hyperbolic",                           
		(Vector2){screen_width/20, screen_height/4}, 75, 5, WHITE);

	DrawTextEx(default_font, "play",                           
		(Vector2){option_horizontal_offset, screen_height*0.45}, 
		option_size, 5, play_color);

	DrawTextEx(default_font, "settings",                           
		(Vector2){option_horizontal_offset, screen_height*0.60}, 
		option_size, 5, settings_color);

	DrawTextEx(default_font, "quit",                           
		(Vector2){option_horizontal_offset, screen_height*0.75}, 
		option_size, 5, quit_color);
	
	if (IsKeyPressed(KEY_UP) && selected > 0) {
		selected-=1;
	} else if (IsKeyPressed(KEY_DOWN) && selected < QUIT) {
		selected+=1;
	} else if (IsKeyPressed(KEY_Z)) {
		main_execute(&selected);
	}
}

void main_execute(int *selected)
{
	switch (*selected) {
	case 0:
		break;
	case 1:
		*selected = 0;
		switch_scene(SETTINGS);
		break;
	case 2:
		exit_window = true;
		break;
	}
}
