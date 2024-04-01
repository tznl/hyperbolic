#include "raylib.h"
#include "include/define.h"

int screen_width;
int screen_height;
int selected = 0;
int current_scene = TITLE;

lua_State *L;

bool exit_window = false;

//setting vars
bool letterbox; 
