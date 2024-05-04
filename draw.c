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
			char buffer[64];
			sprintf(buffer, "%f %f", game->entities->entity.x, game->entities->entity.y);
			draw_game(game);
			DrawText(buffer, 0, 0, 20, BLACK);
			DrawFPS(0, 20);
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
	DrawTexture(game->world_texture, 0, 0, WHITE);
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
