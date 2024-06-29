#include "render.h"

void render_texture(SDL_Texture* texture, SDL_Renderer* renderer, SDL_Rect* src_rect, int x, int y, double angle) {
    SDL_Rect dst_rect;
    dst_rect.x = x - src_rect->w / 2;
    dst_rect.y = y - src_rect->h / 2;
    dst_rect.w = src_rect->w;
    dst_rect.h = src_rect->h;
    SDL_RenderCopyEx(renderer, texture, src_rect, &dst_rect, angle, NULL, SDL_FLIP_NONE);
}

void render_sprite_stack(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y, double angle, int sprite_height) {
    int texture_width, texture_height;
    SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);

    int sprite_count = texture_height / sprite_height;
    SDL_Rect src_height = {0};
    src_height.w = texture_width;
    src_height.h = sprite_height;
    for (int i = sprite_count; i > 0; --i) {
        src_height.y = i * sprite_height;
        render_texture(texture, renderer, &src_height, x, y + i, angle);
    }
}
