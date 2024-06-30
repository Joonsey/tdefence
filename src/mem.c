#include "stdlib.h"
#include "string.h"

void* mem_alloc(int size){
	return malloc(size);
}

void mem_free(void *ptr){
	free(ptr);
}

void mem_copy(void* dest_ptr, void* src_ptr, int size) {
	memcpy(dest_ptr, src_ptr, size);
}

void* mem_realloc(void* ptr, int size) {
	return realloc(ptr, size);
}

/* Set SIZE bytes of DATA to DEST.  */
void mem_set(void *dest, long data, int size) {
	memset(dest, data, size);
}
