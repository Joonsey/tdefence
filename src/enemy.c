#include "enemy.h"
#include "render.h"
#include "defines.h"
#include "mem.h"

Enemy* init_enemy(Enemy* enemy, SDL_Texture* base_texture){
	mem_set(enemy, sizeof(Enemy), 0);
	enemy->base_texture = base_texture;
	enemy->speed = 16.0f;
	enemy->target_index = 0;

	return enemy;
}
void render_enemy(Global *state, Enemy* enemy) {
	render_sprite_stack(
			enemy->base_texture,
			state->renderer,
			enemy->position,
			enemy->angle,
			TILE_SIZE);
}

void place_enemy(Enemy* enemy, Point position) {
	enemy->position = position;
}

int update_enemy(Enemy* enemy, float dt) {
	if (enemy->target_index >= enemy->route.size) {
		printf("INFO: ENEMY hit end of route\n");
		return 1;
	}

	Point target = *(Point*)get_element(&enemy->route, enemy->target_index);
	Point delta = sub_point(target, enemy->position);
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);

	enemy->angle++;

	float velocity = enemy->speed * dt;
	if (distance < velocity) {
		enemy->position = target;
		enemy->target_index++;
	}
	else {
		enemy->position = add_point(enemy->position, mul_point((Point){velocity, velocity}, div_point(delta, (Point){distance, distance})));
	}

	return 0;
}
