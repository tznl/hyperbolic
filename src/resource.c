#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "include/define.h"

struct res *current_res;
void unload_current_res(void) {
	UnloadTexture(current_res->menu_background);	

	UnloadSound(current_res->select_sound);

	UnloadFont(current_res->font);
}

struct res default_res;
void assign_default()
{
	default_res.menu_background =	LoadTexture("assets/default/menu_background.png"),

	default_res.select_sound =	LoadSound("assets/default/select.wav"),

	SetTextureFilter(default_res.font.texture, TEXTURE_FILTER_BILINEAR);
}

struct config config_current;
int config_retrieve(void)
{
	sqlite3 *db;
	sqlite3_stmt *stmt;

	if(sqlite3_open("config.db", &db) != SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
		return 1;
	}

	sqlite3_prepare_v2(db,
		"SELECT value FROM main WHERE option='letterbox'",
		-1, &stmt, NULL);
	sqlite3_step(stmt);
	config_current.letterbox = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);

	sqlite3_prepare_v2(db,
		"SELECT value FROM main WHERE option='fullscreen'",
		-1, &stmt, NULL);
	sqlite3_step(stmt);
	config_current.fullscreen = sqlite3_column_int(stmt, 0);
	sqlite3_finalize(stmt);

	//strings

	sqlite3_prepare_v2(db,
		"SELECT value FROM string WHERE option='language'",
		-1, &stmt, NULL);
	sqlite3_step(stmt);
	char* language_string = malloc(
		strlen((char*)"assets/default/translation/") +
		strlen((char*)sqlite3_column_text(stmt, 0) + 1));
	strcpy(language_string, "assets/default/translation/");
	strcat(language_string, (char*)sqlite3_column_text(stmt, 0));
	sqlite3_finalize(stmt);

	if(sqlite3_open(language_string, &config_current.db_language) 
		!= SQLITE_OK) {
		fprintf(stderr, "Cannot open database: %s\n", 
			sqlite3_errmsg(config_current.db_language));
		sqlite3_close(config_current.db_language);
		return 1;
	}

	free(language_string);
	sqlite3_close(db);
	return 0;
}

void config_free(struct config *config_target)
{
	sqlite3_close(config_target->db_language);
}

struct config config_buffer;
