#include <raylib.h>
#include <raymath.h>

#include "render.h"
#include "state.h"
#include "defines.h"

void render_texture(Texture2D texture, Rectangle src_rect, Vector2 point, double angle) {

	Rectangle dest_rect = src_rect;

	Vector2 origin = {dest_rect.width / 2, dest_rect.height / 2};

	dest_rect.x = point.x + origin.x;
	dest_rect.y = point.y + origin.y;

    DrawTexturePro(texture, src_rect, dest_rect, origin, angle, WHITE);
}

void render_sprite_stack(Texture2D texture, Vector2 point, double angle, int sprite_height) {
	int texture_height = texture.height;
	int texture_width = texture.width;
    int sprite_count = texture_height / sprite_height;
    Rectangle src_rect = {0};
    src_rect.width = texture_width;
    src_rect.height = sprite_height;
    for (int i = sprite_count; i > 0; --i) {
        src_rect.y = i * sprite_height;
		point.y -= 1;
        render_texture(texture, src_rect, point, angle);
    }
}

void render_sprite_sheet(Texture2D texture, Vector2 point, int index) {
	int texture_height = texture.height;
	int texture_width = texture.width;

	if (index > (texture_width / TILE_SIZE) * (texture_height / TILE_SIZE)) {
		printf("ERROR: index: %d out of range\n", index);
	}

	int x = index % (texture_width / TILE_SIZE);
	int y = index / (texture_width / TILE_SIZE);

	Rectangle src_rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    render_texture(texture, src_rect, point, 0);
}

void render_shadow(Global *state, Vector2 position, int rx, int ry) {
	return;
}
