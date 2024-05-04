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

	// if player is not walking, let them walk
	if (!game->entities->entity.is_walking) {
		if (IsKeyPressed(KEY_UP)) { entity_walk(game, &game->entities->entity, DIR_NORTH, true); }
		if (IsKeyPressed(KEY_DOWN)) { entity_walk(game, &game->entities->entity, DIR_SOUTH, true); }
		if (IsKeyPressed(KEY_LEFT)) { entity_walk(game, &game->entities->entity, DIR_WEST, true); }
		if (IsKeyPressed(KEY_RIGHT)) { entity_walk(game, &game->entities->entity, DIR_EAST, true); }
		if (game->entities->entity.anim_frame_counter > 0) {
			if (IsKeyDown(KEY_UP)) {
				entity_walk(game, &game->entities->entity, DIR_NORTH, true);
			}
			if (IsKeyDown(KEY_DOWN)) {
				entity_walk(game, &game->entities->entity, DIR_SOUTH, true);
			}
			if (IsKeyDown(KEY_LEFT)) {
				entity_walk(game, &game->entities->entity, DIR_WEST, true);
			}
			if (IsKeyDown(KEY_RIGHT)) {
				entity_walk(game, &game->entities->entity, DIR_EAST, true);
			}
		}
	}

	// track the camera
	game->camera.target = (Vector2){
		game->entities->entity.x * TILE_SIZE,
		game->entities->entity.y * TILE_SIZE,
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
		cur->entity.box_rec.x = cur->entity.x * TILE_SIZE;
		cur->entity.box_rec.y = cur->entity.y * TILE_SIZE;
		if (cur->entity.is_walking) {
			cur->entity.frame_rec.x = cur->entity.facing * (ANIM_NO_FRAMES + 1) * TILE_SIZE +
				cur->entity.anim_frame_counter * TILE_SIZE;
			entity_walk(game, &cur->entity, cur->entity.facing, false);
		} else {
			cur->entity.frame_rec.x = cur->entity.facing * (ANIM_NO_FRAMES + 1) * TILE_SIZE;
		}

	}
}

static void entity_walk(game_t *game, entity_t *ent, entity_dir_e dir, bool reset_anim) {
	if (reset_anim) {
		ent->anim_frame_counter = 0;
		ent->is_walking = true;
	}

	ent->facing = dir;
	ent->speed = (float)TILE_SIZE / ANIM_NO_FRAMES;

	if (reset_anim) {
		switch (ent->facing) {
			case DIR_NORTH: ent->y--; break;
			case DIR_SOUTH: ent->y++; break;
			case DIR_WEST: ent->x--; break;
			case DIR_EAST: ent->x++; break;
			default: break;
		}
	}

	switch (ent->facing) {
		case DIR_NORTH:
			ent->box_rec.y = (TILE_SIZE * ent->y)
				+ TILE_SIZE - (ent->speed * ent->anim_frame_counter
				* game->delta_time * MAX_FPS);
			break;
			game->camera.target.y = (TILE_SIZE * ent->y)
				+ TILE_SIZE - (ent->speed * ent->anim_frame_counter
				* game->delta_time * MAX_FPS);
		case DIR_SOUTH:
			ent->box_rec.y = (TILE_SIZE * ent->y)
				- TILE_SIZE + (ent->speed * ent->anim_frame_counter
				* game->delta_time * MAX_FPS);
			break;
		case DIR_WEST:
			ent->box_rec.x = (TILE_SIZE * ent->x)
				+ TILE_SIZE - (ent->speed * ent->anim_frame_counter
				* game->delta_time * MAX_FPS);
			break;
		case DIR_EAST:
			ent->box_rec.x = (TILE_SIZE * ent->x)
				- TILE_SIZE + (ent->speed * ent->anim_frame_counter
				* game->delta_time * MAX_FPS);
			break;
		default: break;
	}
}
