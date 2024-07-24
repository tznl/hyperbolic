#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h> 
#include "include/language.h"
#include "include/define.h"
#include "include/codepoints.h"

char* text_1 = NULL;
char* text_2 = NULL;
char* text_3 = NULL;
char* text_4 = NULL;

void test_load_main_menu()
{
	text_1 = text_retrieve(1); 
	text_2 = text_retrieve(2); 
	text_3 = text_retrieve(3); 
	text_4 = text_retrieve(4); 

	char* combined = malloc(
		(size_t)strlen(text_1) + 
		(size_t)strlen(text_2) + 
		(size_t)strlen(text_3) + 
		(size_t)strlen(text_4) + 
		1);

	strcpy(combined, text_1);
	strcat(combined, text_2);
	strcat(combined, text_3);
	strcat(combined, text_4);
	
	screen_load_font(combined);

}

char* text_retrieve(int code)
{
	sqlite3_stmt *stmt;
	int query_length = strlen("SELECT string FROM main WHERE id=000\0");
	char query_buffer[query_length];

	sprintf(query_buffer,
		"SELECT string FROM main WHERE id=%d", 
		code);

	sqlite3_prepare_v2(config_current.db_language, query_buffer,
		-1, &stmt, NULL);
	sqlite3_step(stmt);
	char* string = malloc((size_t)strlen((char*)sqlite3_column_text(stmt, 0))+1); 
	strcpy(string, (char*)sqlite3_column_text(stmt, 0));
	sqlite3_finalize(stmt);
	return string;
}
