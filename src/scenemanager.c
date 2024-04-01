#include "include/scenemanager.h"
#include "include/define.h"

void switch_scene(int scene)
{
	switch (scene) {
		case SETTINGS: 
			current_scene = SETTINGS;
			break;
	}
}
