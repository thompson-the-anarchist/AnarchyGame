#include <raylib.h>
#include <stdlib.h>
#include "game.h"

void shutdown_game(game_t *game) {
	unload_entity_textures(game);
	CloseWindow();
}

static void unload_entity_textures(game_t *game) {
	for (entity_node_t *cur = game->entities; cur != NULL; cur = cur->next) {
		UnloadTexture(cur->entity.texture);
	}
}
