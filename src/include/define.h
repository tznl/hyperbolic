#ifndef DEFINE_H
#define DEFINE_H

#include "raylib.h"

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define RIDX_CONFIG "config"
  
extern int screen_width;                                                          
extern int screen_height;                                                         
extern int selected;
extern int current_scene;

extern bool exit_window;

extern Texture2D menu1;
extern Font default_font;

extern lua_State *L;

enum scene {TITLE = 0, SWITCH, SETTINGS, PLAY};

//setting vars
extern bool letterbox;
#endif
