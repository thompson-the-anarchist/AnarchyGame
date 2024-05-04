#ifndef _ENTITY_H
#define _ENTITY_H

#include <raylib.h>
#include "texture.h"

typedef enum entity_dir_e {
	DIR_NORTH = 0,
	DIR_SOUTH,
	DIR_EAST,
	DIR_WEST,
} entity_dir_e;

typedef struct entity_t {
	int x, y;
	int id;
	int anim_frame_counter;
	float speed;
	bool is_walking;
	entity_dir_e facing;
	char *texture_path;
	Texture2D texture;
	Rectangle frame_rec;
	Rectangle box_rec;
} entity_t;

#endif
