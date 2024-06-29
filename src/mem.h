#pragma once
void* mem_alloc(int size);
void mem_free(void *ptr);
void mem_copy(void* dest_ptr, void* src_ptr, int size);
void mem_set(void *dest, int size, long data);
void* mem_realloc(void* ptr, int size);
