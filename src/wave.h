#pragma once
#include "level.h"
#include "types.h"

typedef struct wave_t {
	Level *level;
	Darray enemies;
	Texture2D base_enemy_texture;
	int remaining_enemies;
	int wave_count;
} Enemy_wave;

Enemy_wave* init_wave(Enemy_wave* wave, Level* level, Texture2D enemy_texture);
void update_wave(Enemy_wave* wave, float dt);
void draw_wave(Enemy_wave* wave, Global *state);
void start_new_wave(Enemy_wave* wave);
