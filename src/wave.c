#include "wave.h"
#include "mem.h"
#include "state.h"
#include "sprites.h"
#include "enemy.h"
#include "render.h"

#define MAX_WAVE 10

static float spawn_cooldown = 0;
static int wave_config[MAX_WAVE] = {
	4,
	5,
	8,
	10,
	14,
	18,
	20,
	25,
	28,
	35
};

Enemy_wave* init_wave(Enemy_wave* wave, Level* level, Texture enemy_texture) {
	mem_set(wave, sizeof(Enemy_wave), 0);

	wave->level = level;
	wave->base_enemy_texture = enemy_texture;
	init_darray(&wave->enemies, 20, sizeof(Enemy));
	wave->remaining_enemies = wave_config[0];

	return wave;
}

void update_wave(Enemy_wave* wave, float dt) {
	Darray cleanup_array;
	init_darray(&cleanup_array, 20, sizeof(int));

	if (wave->remaining_enemies >= 0) {
		if (spawn_cooldown <= 0) {
			Vector2* start_pos = get_element(&wave->level->route, 0);
			Enemy enemy;
			init_enemy(&enemy, wave->base_enemy_texture);
			enemy.route = wave->level->route;
			place_enemy(&enemy, *start_pos);
			add_element(&wave->enemies, &enemy);

			spawn_cooldown = 3;
			wave->remaining_enemies--;
		}

		spawn_cooldown -= dt;
	}

	for (int i = 0; i < wave->enemies.size; i++) {
		Enemy *enemy = get_element(&wave->enemies, i);
		int done = update_enemy(enemy, dt);
		if (done == 1) {
			int n = i;
			add_element(&cleanup_array, &n);
		}
	}

	for (int i = 0; i < cleanup_array.size; i++) {
		int* n = get_element(&cleanup_array, i);
		Enemy *enemy = pop_element(&wave->enemies, *n);
		mem_free(enemy);
	}

	free_darray(&cleanup_array);
}

void start_new_wave(Enemy_wave* wave) {
	if (wave->remaining_enemies >= 0) {
		printf("ERROR: tried starting new wave while there are remaining enemies\n");
		return;
	}
	wave->wave_count++;
	// if you segfault here you beat the game! congratz!
	wave->remaining_enemies = wave_config[wave->wave_count];
}

void draw_wave(Enemy_wave* wave, Global *state) {
	for (int i = 0; i < wave->enemies.size; i++) {
		Enemy *enemy = get_element(&wave->enemies, i);
		Vector2 position = enemy->position;
		position.x += 8;
		position.y += 14;
		render_shadow(state, position, 4, 3);
	}

	for (int i = 0; i < wave->enemies.size; i++) {
		Enemy *enemy = get_element(&wave->enemies, i);
		render_enemy(state, enemy);
	}
}
