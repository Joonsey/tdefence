#include "render.h"
#include "tower.h"

tower* init_tower(global *state, tower* tower, SDL_Texture* base_texture)
{
	tower->range = 10;
	tower->target = NULL;
	tower->angle = 0;
	tower->base_texture = base_texture;

	return tower;
};

void render_tower(global *state, tower* tower)
{
	render_sprite_stack(
			tower->base_texture,
			state->renderer,
			tower->x,
			tower->y,
			tower->angle,
			16);
}

