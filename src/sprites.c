#include "sprites.h"

SDL_Texture* load_sprite(Global *state, char* path){

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		printf("Error loading image: %s\n", IMG_GetError());
	}
	return SDL_CreateTextureFromSurface(state->renderer, surface);
}

SDL_Texture* load_spritesheet(Global *state, char* path){
	return load_sprite(state, path);
}
