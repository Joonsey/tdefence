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

void mem_set(void *dest, int size, long data) {
	memset(dest, size, data);
}
