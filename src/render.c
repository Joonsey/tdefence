#include <SDL2/SDL2_gfxPrimitives.h>

#include "render.h"
#include "state.h"
#include "defines.h"

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src_rect, Point point, double angle) {
    SDL_Rect dst_rect;
    dst_rect.x = point.x;
    dst_rect.y = point.y;
    dst_rect.w = src_rect->w;
    dst_rect.h = src_rect->h;
    SDL_RenderCopyEx(renderer, texture, src_rect, &dst_rect, angle, NULL, SDL_FLIP_NONE);
}

void render_sprite_stack(SDL_Texture* texture, SDL_Renderer* renderer, Point point, double angle, int sprite_height) {
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

    int sprite_count = texture_height / sprite_height;
    SDL_Rect src_height = {0};
    src_height.w = texture_width;
    src_height.h = sprite_height;
    for (int i = sprite_count; i > 0; --i) {
        src_height.y = i * sprite_height;
		point.y -= 1;
        render_texture(texture, renderer, &src_height, point, angle);
    }
}

void render_sprite_sheet(SDL_Texture* texture, SDL_Renderer* renderer, Point point, int index) {
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

	if (index > (texture_width / TILE_SIZE) * (texture_height / TILE_SIZE)) {
		printf("ERROR: index: %d out of range\n", index);
	}

	int x = index % (texture_width / TILE_SIZE);
	int y = index / (texture_width / TILE_SIZE);

	SDL_Rect src_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    render_texture(texture, renderer, &src_rect, point, 0);
}

void render_shadow(Global *state, Point position, int rx, int ry) {
	filledEllipseRGBA(state->renderer, position.x, position.y, rx, ry, 0, 0, 0, 70);
}
