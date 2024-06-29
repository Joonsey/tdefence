#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "types.h"
#include "render.h"
#include "state.h"
#include "defines.h"
#include "sprites.h"

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

	state.is_running = 1;
	SDL_Event e;
	double angle = 0;

	SDL_Texture* texture = load_sprite(&state, "assets/sprites/tank.png");

	while (state.is_running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				state.is_running = 0;
			}
			else if((e.type == SDL_KEYUP) & (e.key.keysym.sym == SDLK_q))
			{
				state.is_running = 0;
			}
		}
		prepare_render(&state);

		render_sprite_stack(texture, state.renderer, RENDER_WIDTH / 2, RENDER_HEIGHT / 2, angle, 16);

		angle++;

		render_render_texture(&state);
		SDL_RenderPresent(state.renderer);
		SDL_Delay(16);
	}

	cleanup_state(&state);
	SDL_Quit();

	return 0;
}
