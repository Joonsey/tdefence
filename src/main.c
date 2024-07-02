#include <raylib.h>
#include <stdio.h>
#include <math.h>

#include "defines.h"
#include "select.h"
#include "sprites.h"
#include "tower.h"
#include "types.h"
#include "state.h"
#include "level.h"
#include "enemy.h"
#include "wave.h"

static Global state;

    int main(int argc, char *argv[]) {
	if (init_global_state(&state) != 0) {
		printf("Error initializing\n");
	}

	Texture2D cannon_texture = load_sprite("assets/sprites/cannon-turret.png");
	Texture2D enemy_texture = load_sprite("assets/sprites/basic_enemy.png");
	Texture2D select_texture = load_sprite("assets/sprites/select.png");
	Texture2D tile_set = load_sprite("assets/map/forestPath_.png");

	state.is_running = 1;
	int draw_path = 0;

	Darray tower_array;
	init_darray(&tower_array, 4, sizeof(Tower));

	Level test_level;
	init_level(&test_level, LEVEL_FIRST, tile_set);

	Select select;
	init_select(&select, &state.hovering, select_texture);

	Enemy_wave wave;
	init_wave(&wave, &test_level, enemy_texture);

	SetTargetFPS(60);

	while (!WindowShouldClose()) {
		state.delta_time = GetFrameTime();
		prepare_render(&state);

		int mouse_x = GetMouseX();
		int mouse_y = GetMouseY();

		float width_ratio = SCREEN_WIDTH / RENDER_WIDTH;
		float height_ratio = SCREEN_HEIGHT / RENDER_HEIGHT;
		mouse_x = mouse_x / width_ratio;
		mouse_y = mouse_y / height_ratio;

		mouse_x = floor(mouse_x / 16) * 16;
		mouse_y = floor(mouse_y / 16) * 16;
		state.hovering = (Vector2){mouse_x, mouse_y};

		render_level(&state, &test_level);

		for (int i = 0; i < tower_array.size; i++) {
			Tower* tower = get_element(&tower_array, i);
			update_tower(tower, state.delta_time, wave.enemies);
			render_tower(&state, tower);
		}

		update_wave(&wave, state.delta_time);
		draw_wave(&wave, &state);

		render_select(&state, &select);

		render_render_texture(&state);
	}

	cleanup_state(&state);

	return 0;
}
