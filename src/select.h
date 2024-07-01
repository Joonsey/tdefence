#pragma once
#include <raylib.h>
#include "types.h"
#include "state.h"

typedef struct select_t {
	Vector2 *point;
	Texture2D texture;
} Select;

Select* init_select(Select* select, Vector2* point, Texture2D texture);
void render_select(Global *state, Select* select);
