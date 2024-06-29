#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct global {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* render_target;
	int is_running;
} global;

int init_global_state(struct global* global);
void render_render_texture(struct global* state);
void cleanup_state(struct global* state);
void prepare_render(global* state);
