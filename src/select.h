#pragma once
#include <SDL2/SDL.h>
#include "types.h"
#include "state.h"

typedef struct select_t {
	Point *point;
	SDL_Texture* texture;
} Select;

Select* init_select(Select* select, Point* point, SDL_Texture* texture);
void render_select(Global *state, Select* select);
