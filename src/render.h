#include <SDL2/SDL.h>
#include <stdio.h>

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src_rect, int x, int y, double angle);

void render_sprite_stack(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, double angle, int sprite_height);
