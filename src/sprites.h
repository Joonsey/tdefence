#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "state.h"

SDL_Texture* load_sprite(global *state, char* path);
