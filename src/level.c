#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "level.h"
#include "render.h"
#include "mem.h"
#include "types.h"
#include "defines.h"

#define file_buff_size 1000

char *strsep(char **stringp, const char *delim) {
    char *rv = *stringp;
    if (rv) {
        *stringp += strcspn(*stringp, delim);
        if (**stringp)
            *(*stringp)++ = '\0';
        else
            *stringp = 0; }
    return rv;
}

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

Vector2 find_start_point(const Level* level, const int path_value) {
	Darray *int_array = get_element(&level->tiles, 0);
	int value = 0;
	int x = -1;
	while (value != path_value) {
		x++;
		if (x >= int_array->size) return (Vector2){0, 0};
		value = *(int*)get_element(int_array, x);
	}

	if (value != path_value) {
		printf("ERROR: start value unbound\n");
		return (Vector2){0, 0};
	}

	return (Vector2){x * TILE_SIZE, 0};
};

Vector2 find_end_point(const Level* level, const int path_value) {
	Darray *int_array = get_element(&level->tiles, level->tiles.size - 1);
	int value = 0;
	int x = -1;
	while (value != path_value) {
		x++;
		if (x >= int_array->size) return (Vector2){0, 0};
		value = *(int*)get_element(int_array, x);
	}

	if (value != path_value) {
		printf("ERROR: end value unbound\n");
		return (Vector2){0, 0};
	}

	return (Vector2){x * TILE_SIZE, level->tiles.size * TILE_SIZE};
};

int get_tile(Level* level, int x, int y) {
	return (*(int*)get_element(get_element(&level->tiles, y), x));
}

int check_point_in_route(Darray routes, Vector2 point)
{
	for (int i = 0; i < routes.size; i++)
	{
		Vector2 route_point = *(Vector2*)get_element(&routes, i);
		if (Vector2Equals(route_point, point)) return 1;
	}
	return 0;
}

Darray determine_route(Level* level) {
	Darray route_array = {0};

	const int path_value = 28;
	Vector2 start_point = find_start_point(level, path_value);
	Vector2 end_point = find_end_point(level, path_value);

	Vector2 current_point = start_point;
	Vector2 old_point = start_point;

	init_darray(&route_array, 50, sizeof(Vector2));
	add_element(&route_array, &start_point);

	int dist = 32;
	while (dist > 16) {
		if (current_point.x > 0) {
			//check left
			Vector2 check_point = old_point;
			check_point.x -= TILE_SIZE;
			if (get_tile(level, check_point.x / TILE_SIZE, check_point.y / TILE_SIZE) == path_value) {
				if (check_point_in_route(route_array, check_point) == 0) {
					current_point = check_point;
				}
			}
		}
		if (current_point.x < (*(Darray*)get_element(&level->tiles, 0)).size * TILE_SIZE) {
			//check right
			Vector2 check_point = old_point;
			check_point.x += TILE_SIZE;
			if (get_tile(level, check_point.x / TILE_SIZE, check_point.y / TILE_SIZE) == path_value) {
				if (check_point_in_route(route_array, check_point) == 0) {
					current_point = check_point;
				}
			}
		}
		if (current_point.y > 0) {
			//check up
			Vector2 check_point = old_point;
			check_point.y -= TILE_SIZE;
			if (get_tile(level, check_point.x / TILE_SIZE, check_point.y / TILE_SIZE) == path_value) {
				if (check_point_in_route(route_array, check_point) == 0) {
					current_point = check_point;
				}
			}
		}
		if (current_point.y < level->tiles.size * TILE_SIZE) {
			//check down
			Vector2 check_point = old_point;
			check_point.y += TILE_SIZE;
			if (get_tile(level, check_point.x / TILE_SIZE, check_point.y / TILE_SIZE) == path_value) {
				if (check_point_in_route(route_array, check_point) == 0) {
					current_point = check_point;
				}
			}
		}

		Vector2 *buff = mem_alloc(sizeof(Vector2));
		*buff = current_point;

		if (Vector2Equals(old_point, current_point)) {
			printf("ERROR");
			break;
		}

		dist = Vector2Distance(current_point, end_point);
		old_point = current_point;
		add_element(&route_array, buff);
	}

	add_element(&route_array, &end_point);

	return route_array;
};

Level* init_level(Level* level, level_type type, Texture2D tile_set) {
	// ignore type for now
	mem_set(level, 0, sizeof(*level));
	level->type = type;

	level->tiles = read_file("assets/map/level1.csv");
	level->tilesheet = tile_set;

	level->route = determine_route(level);
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

void render_route(Global* state, Level* level) {
//	for (int i = 0; i < level->route.size; i ++) {
//		Point point = *(Point*)get_element(&level->route, i);
//
//		const SDL_Rect rect = {point.x, point.y, 16, 16};
//		SDL_SetRenderDrawColor(state->renderer, 0,0,255,255);
//		SDL_RenderFillRect(state->renderer, &rect);
//		SDL_RenderDrawRect(state->renderer, &rect);
//		SDL_SetRenderDrawColor(state->renderer, 0,0,0,255);
//	}
}

void render_level(Global* state, Level* level) {
	for (int y = 0; y < level->tiles.size; y ++) {
		Darray *int_array = get_element(&level->tiles, y);
		for (int x = 0; x < int_array->size ; x ++) {
			int value = *(int*)get_element(int_array, x);
			Vector2 point = {x * 16, y * 16};
			render_sprite_sheet(level->tilesheet, point, value);
		}
	}
}
