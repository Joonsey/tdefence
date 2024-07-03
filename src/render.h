#pragma once
#include <stdio.h>

#include "types.h"
#include "state.h"

void init_render();
void render_texture(Texture2D texture, Rectangle src_rect, Vector2 point, double angle);
void render_sprite_stack(Texture2D texture, Vector2 point, double angle, int sprite_height);
void render_sprite_sheet(Texture2D texture, Vector2 point, int index);
void render_shadow(Global *state, Vector2 position, int rx, int ry);
void render_sprite_stack_with_outline(Texture2D texture, Vector2 point, double angle, int sprite_height, float outline_color[4], float outline_size);
void render_outline(Texture2D texture, float outline_color[4], float outline_size);
