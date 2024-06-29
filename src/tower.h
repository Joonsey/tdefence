#pragma once
#include <SDL2/SDL.h>
#include "state.h"

typedef struct tower_t {
	void* target;
	float range;
	double angle;
	int x, y;
	SDL_Texture* base_texture;
} tower;


tower* init_tower(global *state, tower* tower);
void render_tower(global *state, tower* tower);
