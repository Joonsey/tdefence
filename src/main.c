#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "sprites.h"
#include "tower.h"
#include "types.h"
#include "state.h"

static global state;

#ifdef _WIN32
#include <windows.h>
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
#else
    int main(int argc, char *argv[]) {
#endif
	if (init_global_state(&state) != 0) {
		printf("Error initializing\n");
	}

	SDL_Texture* tex = load_sprite(&state, "assets/sprites/cannon-turret.png");

	state.is_running = 1;
	SDL_Event e;

	darray tower_array;
	init_darray(&tower_array, 4, sizeof(tower));

	for (int i = 0; i < 20; i ++)
	{
		tower tower;
		init_tower(&state, &tower, tex);
		tower.x = 16* i;
		tower.y = 200;
		tower.angle = i * 10;
		add_element(&tower_array, &tower);
	}

	pop_element(&tower_array, 3);


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
					tower tower;
					init_tower(&state, &tower, tex);
					tower.x = 16 * (tower_array.size % 20);
					tower.y = 100;
					add_element(&tower_array, &tower);
				}
				if (e.key.keysym.sym == SDLK_d){
					tower* tower = pop_element(&tower_array, tower_array.size - 1);
				}
			}
		}
		prepare_render(&state);

		for (int i = 0; i < tower_array.size; i++) {
			tower* tower = get_element(&tower_array, i);
			render_tower(&state, tower);
			tower->angle++;
		}

		render_render_texture(&state);
		SDL_RenderPresent(state.renderer);
		SDL_Delay(16);
	}

	cleanup_state(&state);
	SDL_Quit();

	return 0;
}
