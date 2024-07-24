#include "include/codepoints.h"
#include "include/define.h"
#include "raylib.h"
#include <string.h>
#include <stdio.h>

int *CodepointRemoveDuplicates
	(int *codepoints, int codepointCount, int *codepointsResultCount)
{
	int codepointsNoDupsCount = codepointCount;
	int *codepointsNoDups = (int *)calloc(codepointCount, sizeof(int));
	memcpy(codepointsNoDups, codepoints, codepointCount*sizeof(int));

/* Remove duplicates */
	int i;
	for (i = 0; i < codepointsNoDupsCount; i++)
	{
		int j;
		for (j = i + 1; j < codepointsNoDupsCount; j++)
		{
			if (codepointsNoDups[i] == codepointsNoDups[j])
			{
				int k;
				for (k = j; k < codepointsNoDupsCount; k++) 
					codepointsNoDups[k] = 
						codepointsNoDups[k + 1];

				codepointsNoDupsCount--;
				j--;
			}
		}
	}   

/* NOTE: The size of codepointsNoDups is the same as original array but
only required positions are filled (codepointsNoDupsCount) */

	*codepointsResultCount = codepointsNoDupsCount;
	return codepointsNoDups;
}

void screen_load_font(char* string)
{
	sqlite3_stmt *stmt;
	
        int codepointCount = 0;
	int *codepoints = LoadCodepoints(string, &codepointCount);
        int codepointsNoDupsCount = 0;
        int *codepointsNoDups = CodepointRemoveDuplicates(
                        codepoints,
                        codepointCount,
                        &codepointsNoDupsCount);

	sqlite3_prepare_v2(config_current.db_language, 
		"SELECT font FROM metadata", -1, &stmt, NULL);
	sqlite3_step(stmt);
	char* path = "assets/default/font/";
	char* font_name = (char*)sqlite3_column_text(stmt, 0);
	char* font_path = malloc(
		strlen(path) +
		strlen(font_name) +
		+ 1);
	strcpy(font_path, path);
	strcat(font_path, font_name);
	sqlite3_finalize(stmt);

        UnloadCodepoints(codepoints);

        current_res->font = LoadFontEx(font_path,
                50,
                codepointsNoDups,
                codepointsNoDupsCount); 

	free(font_path);
	free(codepointsNoDups);
}   
