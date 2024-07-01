#pragma once
#include "types.h"
#include "state.h"

typedef struct enemy_t {
	Vector2 position;
	float speed;
	float angle;
	int health;
	int target_index;
	Darray route;
	Texture  base_texture;
} Enemy;

Enemy* init_enemy(Enemy* enemy, Texture base_texture);
void place_enemy(Enemy* enemy, Vector2 position);
void render_enemy(Global *state, Enemy* enemy);
int update_enemy(Enemy* enemy, float dt);
