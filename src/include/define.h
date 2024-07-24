#ifndef DEFINE_H
#define DEFINE_H

#include "raylib.h"
#include <sqlite3.h>

#define RIDX_CONFIG "config"
  
enum scene {TITLE = 0, SWITCH, SETTINGS, PLAY};

struct res
{
        Texture2D menu_background;
        Sound select_sound;
        Font font;
}; 

struct config
{
	bool fullscreen;
	bool letterbox;
	sqlite3* db_language;
};

extern struct res *current_res;
extern struct res default_res;
extern struct config config_current;
extern struct config config_buffer;

extern int screen_width;                                                          
extern int screen_height;                                                         
extern int selected;
extern int current_scene;

extern bool exit_window;

void assign_default(void);
void unload_current_res(void);
void config_buffer_assign(void);
void config_free(struct config *config_target);

int config_retrieve(void);

extern char* codepoint_text;

#endif
