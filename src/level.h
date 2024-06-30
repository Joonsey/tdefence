#pragma once
#include "state.h"
#include "types.h"

typedef enum level_type {
	LEVEL_FIRST
} level_type;


typedef struct level_t {
	level_type type;
	Darray tiles;
	Darray route;
} Level;

Level* init_level(Level* level, level_type);
void render_level(Global* state, Level* level);
void render_route(Global* state, Level* level);
void debug_level(Level* level);
