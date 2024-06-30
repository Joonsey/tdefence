#pragma once
#include "level.h"
#include "enemy.h"
#include "types.h"

typedef struct wave_t {
	Level *level;
	Darray enemies;
	SDL_Texture* base_enemy_texture;
	int remaining_enemies;
	int wave_count;
} Wave;

Wave* init_wave(Wave* wave, Level* level, SDL_Texture* enemy_texture);
void update_wave(Wave* wave, float dt);
void draw_wave(Wave* wave, Global *state);
