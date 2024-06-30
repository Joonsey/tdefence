#pragma once
#include <SDL2/SDL.h>
#include "state.h"
#include "types.h"

typedef struct tower_t {
	void* target;
	float range;
	double angle;
	Point point;
	SDL_Texture* base_texture;
} Tower;


Tower* init_tower(Global *state, Tower* tower, SDL_Texture* base_texture);
void render_tower(Global *state, Tower* tower);
