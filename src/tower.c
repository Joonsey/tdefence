#include "tower.h"
#include "defines.h"
#include "render.h"

Tower* init_tower(Tower* tower, SDL_Texture* base_texture)
{
	tower->range = 10;
	tower->target = NULL;
	tower->angle = 0;
	tower->base_texture = base_texture;

	return tower;
};

void render_tower(Global *state, Tower* tower)
{
	render_sprite_stack(
			tower->base_texture,
			state->renderer,
			tower->point,
			tower->angle,
			TILE_SIZE);
}

