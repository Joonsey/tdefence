#pragma once
#include <SDL2/SDL.h>
#include "types.h"
#include "state.h"

typedef struct enemy_t {
	Point position;
	float speed;
	float angle;
	int target_index;
	Darray route;
	SDL_Texture* base_texture;
} Enemy;

Enemy* init_enemy(Enemy* enemy, SDL_Texture* base_texture);
void place_enemy(Enemy* enemy, Point position);
void render_enemy(Global *state, Enemy* enemy);
int update_enemy(Enemy* enemy, float dt);
