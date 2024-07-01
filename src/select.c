#include "select.h"
#include "mem.h"
#include "render.h"

Select* init_select(Select* select, Vector2* point, Texture2D texture) {
	mem_set(select, sizeof(Select), 0);

	select->point = point;
	select->texture = texture;

	return select;
}

void render_select(Global *state, Select* select) {
	render_sprite_stack(select->texture, *select->point, 0, 16);
}
