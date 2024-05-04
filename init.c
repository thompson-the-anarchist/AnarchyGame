#include <raylib.h>
#include <stdlib.h>
#include "entity.h"
#include "game.h"
#include "sglib.h"

game_t *init_game(void) {
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_NAME);
	SetTargetFPS(MAX_FPS);

	game_t *game = calloc(1, sizeof(game_t));

	game->frame_counter = 0;
	game->delta_time = 0;

	game->camera.zoom = CAMERA_ZOOM;
	game->camera.offset = (Vector2){(float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2};

	game->state = MENU;
	game->entities = NULL;
	game->no_entities = 0;

	game->path_to_texture = "assets/city/simplified/Level_0/Tiles.png";

	entity_t player = (entity_t) {
		.id = 0,
		.x = 5,
		.y = 5,
		.box_rec = (Rectangle){
			.x = player.x * TILE_SIZE,
			.y = player.y * TILE_SIZE,
			.width = TILE_SIZE, .height = TILE_SIZE,
		},
		.frame_rec = (Rectangle){
			.x = 0,
			.y = 0,
			.width = TILE_SIZE, .height = TILE_SIZE,
		},
		.facing = DIR_SOUTH,
		.texture_path = "assets/player.png",
		.anim_frame_counter = 0,
		.is_walking = false,
		.speed = 0.0f,
	};

	entity_node_t *player_node = calloc(1, sizeof(entity_node_t));
	player_node->entity = player;
	player_node->next = NULL;

	SGLIB_LIST_ADD(entity_node_t, game->entities, player_node, next);

	game->world_texture = LoadTexture(game->path_to_texture);
	load_entity_textures(game);
	return game;
}

static void load_entity_textures(game_t *game) {
	for (entity_node_t *cur = game->entities; cur != NULL; cur = cur->next) {
		cur->entity.texture = LoadTexture(cur->entity.texture_path);
	}
}
