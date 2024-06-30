#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <math.h>

#include "sprites.h"
#include "tower.h"
#include "types.h"
#include "state.h"
#include "level.h"
#include "enemy.h"

static Global state;

#ifdef _WIN32
#include <windows.h>
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
    int main(int argc, char *argv[]) {
#endif
	if (init_global_state(&state) != 0) {
		printf("Error initializing\n");
	}

	SDL_Texture* cannon_texture = load_sprite(&state, "assets/sprites/cannon-turret.png");
	SDL_Texture* enemy_texture = load_sprite(&state, "assets/sprites/basic_enemy.png");

	state.is_running = 1;
	SDL_Event e;
	int draw_path = 0;

	Darray tower_array;
	init_darray(&tower_array, 4, sizeof(Tower));

	for (int i = 0; i < 20; i ++)
	{
		Tower tower;
		init_tower(&tower, cannon_texture);
		Point point = {.x = 16 * i, .y = 200};
		tower.angle = i * 10;
		tower.point = point;
		add_element(&tower_array, &tower);
	}

	pop_element(&tower_array, 3);

	Level test_level;
	init_level(&test_level, LEVEL_FIRST);

	Darray enemy_array;
	init_darray(&enemy_array, 10, sizeof(Enemy));
	Point start_pos = *(Point*)get_element(&test_level.route, 0);

	Enemy enemy;
	init_enemy(&enemy, enemy_texture);
	enemy.route = test_level.route;
	place_enemy(&enemy, start_pos);
	add_element(&enemy_array, &enemy);
	float enemy_spawn_cd = 0;

	while (state.is_running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				state.is_running = 0;
			}
			else if(e.type == SDL_KEYUP) {
				if (e.key.keysym.sym == SDLK_q){
					state.is_running = 0;
				}
				if (e.key.keysym.sym == SDLK_a){
					Tower tower;
					init_tower(&tower, cannon_texture);
					tower.point.x  = 16 * (tower_array.size % 20);
					tower.point.y = 100;
					add_element(&tower_array, &tower);
				}
				if (e.key.keysym.sym == SDLK_d){
					Tower* tower = pop_element(&tower_array, tower_array.size - 1);
				}
				if (e.key.keysym.sym == SDLK_e){
					if (draw_path == 0) draw_path = 1;
					else draw_path = 0;
				}
			}
		}
		uint32_t tick_time = SDL_GetTicks();
		state.delta_time = (tick_time - state.last_tick_time);
		state.delta_time /= 100;
		state.last_tick_time = tick_time;

		prepare_render(&state);

		if (draw_path == 0){
			render_level(&state, &test_level);
		}
		else{
			render_route(&state, &test_level);
		}

		for (int i = 0; i < tower_array.size; i++) {
			Tower* tower = get_element(&tower_array, i);
			render_tower(&state, tower);
			tower->angle++;
		}

		for (int i = 0; i < enemy_array.size; i++) {
			Enemy *enemy = get_element(&enemy_array, i);
			update_enemy(enemy, state.delta_time);
			render_enemy(&state, enemy);
		}

		if ((state.last_tick_time / 1000) % 3 == 0 & enemy_spawn_cd <= 0) {
			Enemy enemy;
			init_enemy(&enemy, enemy_texture);
			enemy.route = test_level.route;
			place_enemy(&enemy, start_pos);
			add_element(&enemy_array, &enemy);
			enemy_spawn_cd = 1;
		}

		enemy_spawn_cd -= state.delta_time;

		render_render_texture(&state);
		SDL_RenderPresent(state.renderer);
		SDL_Delay(16);
	}

	cleanup_state(&state);
	SDL_Quit();

	return 0;
}
