#include "render.h"
#include "types.h"
#include "tower.h"
#include "sprites.h"

tower* init_tower(global *state, tower* tower)
{
	tower->range = 10;
	tower->target = NULL;
	tower->angle = 0;
	tower->base_texture = load_sprite(state, "assets/sprites/cannon-turret.png");

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

