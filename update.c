#include <raylib.h>
#include <stdlib.h>
#include "entity.h"
#include "game.h"

void update_frame(game_t *game) {
	game->frame_counter++;
	game->delta_time = GetFrameTime();

	switch (game->state) {
		case MENU:
			if (IsKeyPressed(KEY_SPACE)) {
				game->state = PLAYING;
			}
			break;
		case PLAYING:
			update_game(game);
			if (IsKeyPressed(KEY_BACKSPACE)) {
				game->state = GAME_OVER;
			}
			break;
		case GAME_OVER:
			if (IsKeyPressed(KEY_SPACE)) {
				game->state = MENU;
			}
			break;
		default:
			break;
	}
}

static void update_game(game_t *game) {
	if (IsKeyDown(KEY_UP)) {
		game->entities->entity.box_rec.y -= PLAYER_SPEED * game->delta_time;
		game->entities->entity.facing = DIR_NORTH;
		game->entities->entity.is_walking = true;
	};
	if (IsKeyDown(KEY_DOWN)) {
		game->entities->entity.box_rec.y += PLAYER_SPEED * game->delta_time;
		game->entities->entity.facing = DIR_SOUTH;
		game->entities->entity.is_walking = true;
	};
	if (IsKeyDown(KEY_LEFT)) {
		game->entities->entity.box_rec.x -= PLAYER_SPEED * game->delta_time;
		game->entities->entity.facing = DIR_WEST;
		game->entities->entity.is_walking = true;
	};
	if (IsKeyDown(KEY_RIGHT)) {
		game->entities->entity.box_rec.x += PLAYER_SPEED * game->delta_time;
		game->entities->entity.facing = DIR_EAST;
		game->entities->entity.is_walking = true;
	};

	game->camera.target = (Vector2){
		game->entities->entity.box_rec.x,
		game->entities->entity.box_rec.y,
	};

	// check all other entities
	update_entities(game);
}

static void update_entities(game_t *game) {
	for (entity_node_t *cur = game->entities; cur != NULL; cur = cur->next) {
		if (game->frame_counter >= 60/ANIM_FRAME_FRAMES) {
			cur->entity.anim_frame_counter++;
			game->frame_counter = 0;
		}
		if (cur->entity.anim_frame_counter > 1) {
			cur->entity.anim_frame_counter = 0;
			cur->entity.is_walking = false;
			cur->entity.speed = 0;
		}
		if (cur->entity.is_walking) {
			cur->entity.frame_rec.x = cur->entity.facing * (ANIM_NO_FRAMES + 1) * TILE_SIZE +
				cur->entity.anim_frame_counter * TILE_SIZE;
		} else {
			cur->entity.frame_rec.x = cur->entity.facing * (ANIM_NO_FRAMES + 1) * TILE_SIZE;
		}
		cur->entity.x = cur->entity.box_rec.x / TILE_SIZE;
		cur->entity.y = cur->entity.box_rec.y / TILE_SIZE;

	}
}
