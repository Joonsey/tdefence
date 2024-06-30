#include <SDL2/SDL_render.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "level.h"
#include "mem.h"
#include "types.h"

#define file_buff_size 1000


Darray read_file(const char* path) {
	FILE* file = fopen(path, "r");
	char buff[file_buff_size ];
	Darray array;
	init_darray(&array, 40, sizeof(Darray));
	while(fgets(buff, file_buff_size, file)) {
		Darray int_array;
		init_darray(&int_array, 40, sizeof(int));
		char* sep_buff = buff;
		char* split_buff;
		while ((split_buff = strsep(&sep_buff, ",")) != NULL) {
			int l = strtol(split_buff, NULL, 0);
			add_element(&int_array, &l);
		}
		add_element(&array, &int_array);
	}

	return array;
};

Level* init_level(Level* level, level_type type) {
	// ignore type for now
	mem_set(level, sizeof(*level), 0);
	level->type = type;

	Darray array = read_file("assets/map/level1.");
	level->tiles = array;

	debug_level(level);
	return level;
};

void debug_level(Level* level) {
	for (int y = 0; y < level->tiles.size; y ++) {
		Darray *int_array = get_element(&level->tiles, y);
		for (int x = 0; x < int_array->size ; x ++) {
			int value = *(int*)get_element(int_array, x);
			printf("%d ", value);
		}
		printf("\n");
	}
}

void render_level(Global* state, Level* level) {
	for (int y = 0; y < level->tiles.size; y ++) {
		Darray *int_array = get_element(&level->tiles, y);
		for (int x = 0; x < int_array->size ; x ++) {
			int value = *(int*)get_element(int_array, x);
			if (value == 28) {
				const SDL_Rect rect = {x * 16, y * 16, 16, 16};
				SDL_SetRenderDrawColor(state->renderer, 255,0,0,255);
				SDL_RenderFillRect(state->renderer, &rect);
				SDL_RenderDrawRect(state->renderer, &rect);
				SDL_SetRenderDrawColor(state->renderer, 0,0,0,255);
			}
		}
	}
}
