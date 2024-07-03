#include <raylib.h>
#include <raymath.h>
#include "enemy.h"
#include "render.h"
#include "defines.h"
#include "mem.h"
#include "math.h"

Enemy* init_enemy(Enemy* enemy, Texture2D base_texture){
	mem_set(enemy, 0, sizeof(Enemy));
	enemy->base_texture = base_texture;
	enemy->speed = 16.0f;
	enemy->health = 100;

	return enemy;
}
void render_enemy(Global *state, Enemy* enemy) {
	float outline_color[4] = { 0.f, 0.f, 0.f, 1.f };
	render_sprite_stack_with_outline(
			enemy->base_texture,
			enemy->position,
			enemy->angle,
			TILE_SIZE,
			outline_color,
			1.f
			);
}

void place_enemy(Enemy* enemy, Vector2 position) {
	enemy->position = position;
}

int update_enemy(Enemy* enemy, float dt) {
	if (enemy->target_index >= enemy->route.size) {
		printf("INFO: ENEMY hit end of route\n");
		return 1;
	}

	if (enemy->health <= 0)
	{
		// enemy has died
		return 1;
	}

	Vector2 target = *(Vector2*)get_element(&enemy->route, enemy->target_index);
	Vector2 delta = Vector2Subtract(target, enemy->position);
	float distance = sqrt(delta.x * delta.x + delta.y * delta.y);

	enemy->angle++;

	float velocity = enemy->speed * dt;
	if (distance < velocity) {
		enemy->position = target;
		enemy->target_index++;
	}
	else {
		enemy->position = Vector2Add(enemy->position, Vector2Multiply((Vector2){velocity, velocity}, Vector2Divide(delta, (Vector2){distance, distance})));
	}

	return 0;
}
