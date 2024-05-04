#include <raylib.h>
#include <stdlib.h>
#include <stdio.h>
#include "game.h"

void draw_frame(game_t *game) {
	BeginDrawing();
	switch (game->state) {
		case MENU:
			ClearBackground(BLACK);
			break;
		case PLAYING:
			ClearBackground(GRAY);
			draw_game(game);
			break;
		case GAME_OVER:
			ClearBackground(RED);
			break;
		default:
			break;
	}
	EndDrawing();
}

static void draw_game(game_t *game) {
	BeginMode2D(game->camera);
	for (entity_node_t *cur = game->entities; cur != NULL; cur = cur->next) {
		DrawTexturePro(
			cur->entity.texture,
			cur->entity.frame_rec,
			cur->entity.box_rec,
			(Vector2){0, 0},
			0.0f,
			WHITE
		);
	}
	EndMode2D();
}
