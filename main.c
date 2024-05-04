#include <raylib.h>
#include <stdio.h>
#include "game.h"

int main(void) {
	game_t *game = init_game();

	while (!WindowShouldClose()) {
	 	update_frame(game);
	 	draw_frame(game);
	}

	shutdown_game(game);

	return 0;
}
