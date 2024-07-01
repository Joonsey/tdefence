#pragma once

#include <raylib.h>
#include <stdio.h>
#include "types.h"

typedef struct Global {
	int is_running;
	float delta_time;
	RenderTexture render_texture;
	unsigned long long last_tick_time;
	Vector2 hovering;
} Global;

int init_global_state(Global* global);
void render_render_texture(Global* state);
void cleanup_state(Global* state);
void prepare_render(Global* state);
