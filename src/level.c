#include "level.h"
#include "mem.h"
#include <SDL2/SDL_render.h>


level* init_level(level* level, level_type type) {
	// ignore type for now
	mem_set(level, sizeof(*level), 0);
	level->type = type;

	// making stuff up for now
	level->tiles[4][10] = 1;
	level->tiles[4][11] = 1;
	level->tiles[4][12] = 1;

	return level;
};

void render_level(global* state, level* level) {
	for (int y = 0; y < 44; y ++) {
		for (int x = 0; x < 67; x ++) {
			int tile = level->tiles[y][x];
			if (tile == 1) {

				const SDL_Rect rect = {x * 16, y * 16, 16, 16};
				SDL_SetRenderDrawColor(state->renderer, 255,0,0,255);
				SDL_RenderFillRect(state->renderer, &rect);
				SDL_RenderDrawRect(state->renderer, &rect);
				SDL_SetRenderDrawColor(state->renderer, 0,0,0,255);
			}
		}
	}
}
