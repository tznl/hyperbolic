#include "include/codepoints.h"
#include "include/define.h"
#include "raylib.h"
#include <string.h>

int *CodepointRemoveDuplicates(int *codepoints, int codepointCount, int *codepointsResultCount)
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
				for (k = j; k < codepointsNoDupsCount; k++) codepointsNoDups[k] = codepointsNoDups[k + 1];

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

void screen_load_font()
{
        int codepointCount = 0;
	int *codepoints = LoadCodepoints(codepoint_text, &codepointCount);
        int codepointsNoDupsCount = 0;
        int *codepointsNoDups = CodepointRemoveDuplicates(
                        codepoints,
                        codepointCount,
                        &codepointsNoDupsCount);

        UnloadCodepoints(codepoints);

        current_res->font = LoadFontEx("assets/default/font/"
		"DoolittleGaramond-Italic.otf",
                50,
                codepointsNoDups,
                codepointsNoDupsCount); 

	free(codepointsNoDups);
}   
