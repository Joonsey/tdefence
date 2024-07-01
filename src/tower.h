#pragma once
#include "state.h"
#include "types.h"
#include "enemy.h"

typedef struct tower_t {
	Enemy* target;
	float range;
	double angle;
	Vector2 point;
	int damage;
	float cooldown;
	Texture2D base_texture;
} Tower;

Tower* init_tower(Tower* tower, Texture2D base_texture);
void render_tower(Global *state, Tower* tower);
void update_tower(Tower* tower, float dt, const Darray enemies);
