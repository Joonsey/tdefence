#pragma once
#include <SDL2/SDL.h>
#include "state.h"
#include "types.h"
#include "enemy.h"

typedef struct tower_t {
	Enemy* target;
	float range;
	double angle;
	Point point;
	int damage;
	float cooldown;
	SDL_Texture* base_texture;
} Tower;

Tower* init_tower(Tower* tower, SDL_Texture* base_texture);
void render_tower(Global *state, Tower* tower);
void update_tower(Tower* tower, float dt, const Darray enemies);
