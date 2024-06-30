#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

typedef struct Global {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* render_target;
	int is_running;
} Global;

int init_global_state(Global* global);
void render_render_texture(Global* state);
void cleanup_state(Global* state);
void prepare_render(Global* state);
