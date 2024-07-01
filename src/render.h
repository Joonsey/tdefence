#pragma once
#include <SDL2/SDL.h>
#include <stdio.h>

#include "types.h"

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src_rect, Point point, double angle);
void render_sprite_stack(SDL_Texture* texture, SDL_Renderer* renderer, Point point, double angle, int sprite_height);
void render_sprite_sheet(SDL_Texture* texture, SDL_Renderer* renderer, Point point, int index);
