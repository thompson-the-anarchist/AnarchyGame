#ifndef _GAME_H
#define _GAME_H

#include <raylib.h>
#include "entity.h"
#include "sglib.h"

#define TILE_SIZE 16
#define CAMERA_ZOOM 4.0f
#define ANIM_FRAME_FRAMES 10
#define ANIM_NO_FRAMES 3

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 640

#define MAX_FPS 60
#define GAME_NAME "ANARCHY"

typedef enum game_state_e {
	MENU,
	PLAYING,
	GAME_OVER,
} game_state_e;

typedef struct entity_node_t {
	entity_t entity;
	struct entity_node_t *next;
} entity_node_t;

typedef struct game_t {
	int frame_counter;
	float delta_time;

	Camera2D camera;
	game_state_e state;

	entity_node_t *entities;
	int no_entities;

	Texture2D world_texture;
	char *path_to_texture;
} game_t;

game_t *init_game(void);
static void load_entity_textures(game_t *game);

void update_frame(game_t *game);
static void update_game(game_t *game);
static void update_entities(game_t *game);
static void entity_walk(game_t *game, entity_t *ent, entity_dir_e dir, bool reset_anim);

void draw_frame(game_t *game);
static void draw_game(game_t *game);

void shutdown_game(game_t *game);
static void unload_entity_textures(game_t *game);

#endif
