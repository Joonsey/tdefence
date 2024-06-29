#include "state.h"
#include "defines.h"


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

void prepare_render(global* state)
{
	if (SDL_SetRenderTarget(state->renderer, state->render_target) != 0) {
		printf("SDL_SetRenderTarget Error: %s\n", SDL_GetError());
	}
	SDL_RenderClear(state->renderer);
}

