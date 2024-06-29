#include "state.h"

typedef enum level_type {
	LEVEL_FIRST
} level_type;


typedef struct level_t {
	int tiles[68][45];
	level_type type;
} level;

level* init_level(level* level, level_type);
void render_level(global* state, level* level);

