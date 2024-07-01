#include <raylib.h>
#include <raymath.h>
#include <math.h>
#include "tower.h"
#include "defines.h"
#include "render.h"

Tower* init_tower(Tower* tower, Texture2D base_texture)
{
	tower->range = 80;
	tower->target = NULL;
	tower->angle = 0;
	tower->base_texture = base_texture;
	tower->cooldown = 2;
	tower->damage = 50;

	return tower;
};

void shoot_enemy(Tower* tower, Enemy* enemy) {
	enemy->health -= tower->damage;
	tower->cooldown = 2;
}

void render_tower(Global *state, Tower* tower)
{
	render_sprite_stack(
			tower->base_texture,
			tower->point,
			tower->angle,
			TILE_SIZE);
}

void update_tower(Tower* tower, float dt, const Darray enemies) {

	tower->target = NULL;
	for (int i = 0; i < enemies.size; i++) {
		Enemy *enemy = get_element(&enemies, i);
		int dist = Vector2Distance(enemy->position, tower->point);

		if (dist <= tower->range) {
			tower->target = enemy;
			continue;
		}
	}

	if (tower->cooldown < dt) tower->cooldown = 0;
	if (tower->cooldown > 0) tower->cooldown -= dt;

	if ((tower->target) && (tower->cooldown <= 0)) {
		Vector2 delta = Vector2Subtract(tower->point, tower->target->position);
		//TODO
		//tower->angle = angle_from_point(delta);
		shoot_enemy(tower, tower->target);
	}
}
