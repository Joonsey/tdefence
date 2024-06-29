#include "sprites.h"

SDL_Texture* load_sprite(global *state, char* path){

	SDL_Surface* surface = IMG_Load(path);
	if (surface == NULL) {
		printf("Error loading image: %s\n", IMG_GetError());
	}
	return SDL_CreateTextureFromSurface(state->renderer, surface);

}
