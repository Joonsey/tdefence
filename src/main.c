#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "types.h"
#include "render.h"

#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 720

#define RENDER_WIDTH 360
#define RENDER_HEIGHT 420

struct global {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* render_target;
	int is_running;
} global;

int init_global_state(struct global* global)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("SDL_Init Error: %s\n", SDL_GetError());
		return 1;
	}

	global->window = SDL_CreateWindow("Tower Defence", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (global->window == NULL) {
		printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	global->renderer = SDL_CreateRenderer(global->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (global->renderer == NULL) {
		SDL_DestroyWindow(global->window);
		printf("SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	global->render_target = SDL_CreateTexture(global->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, RENDER_WIDTH, RENDER_HEIGHT);
	if (global->render_target == NULL) {
		SDL_DestroyWindow(global->window);
		printf("SDL_CreateTexture Error: %s\n", SDL_GetError());
		SDL_Quit();
		return 1;
	}

	return 0;
};

void render_render_texture(struct global* state)
{
	SDL_SetRenderTarget(state->renderer, NULL);
	SDL_RenderClear(state->renderer);
	SDL_Rect src_rect = {0, 0, RENDER_WIDTH, RENDER_HEIGHT};
	SDL_Rect dst_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
	if (SDL_RenderCopy(state->renderer, state->render_target, &src_rect, &dst_rect) != 0) {
		printf("SDL_RenderCopy Error: %s\n", SDL_GetError());
	}
}

void cleanup_state(struct global* state)
{
	SDL_DestroyRenderer(state->renderer);
	SDL_DestroyWindow(state->window);
}

int main(int argc, char *argv[]) {
	struct global state = {0};

	if (init_global_state(&state) != 0) {
		printf("Error initializing\n");
	}

	state.is_running = 1;
	SDL_Event e;
	double angle = 0;

    SDL_Surface* surface = IMG_Load("assets/sprites/tank.png");
	if (surface == NULL) {
    printf("Error loading image: %s\n", IMG_GetError());
    return 1;
}
    SDL_Texture* texture = SDL_CreateTextureFromSurface(state.renderer, surface);

	while (state.is_running) {
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				state.is_running = 0;
			}
		}
		if (SDL_SetRenderTarget(state.renderer, state.render_target) != 0) {
            printf("SDL_SetRenderTarget Error: %s\n", SDL_GetError());
		}
		SDL_RenderClear(state.renderer);

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
