#include "state.h"
#include "defines.h"


int init_global_state(Global* global)
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Tower Defence");

	global->render_texture = LoadRenderTexture(RENDER_WIDTH, RENDER_HEIGHT);

	global->last_tick_time = 0;
	global->delta_time = 0;

	return 0;
};

void prepare_render(Global* state)
{
	BeginTextureMode(state->render_texture);
	ClearBackground(RAYWHITE);
}

void render_render_texture(Global* state)
{
	EndTextureMode();
	BeginDrawing();
	DrawTexturePro(
			state->render_texture.texture,
			(Rectangle){ 0, 0, state->render_texture.texture.width, -state->render_texture.texture.height },
			(Rectangle){ 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT },
			(Vector2){ 0, 0 },
			0.0f,
			WHITE
			);
    EndDrawing();
}

void cleanup_state(Global* state)
{
	UnloadRenderTexture(state->render_texture);
	CloseWindow();
}
