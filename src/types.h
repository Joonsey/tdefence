#pragma once
#include "stdio.h"

typedef struct darray_t {
    void *array;
    size_t  element_size;
    size_t size;
    size_t capacity;
} darray;

void init_darray(darray *arr, size_t initial_capacity, size_t size);
void resize_darray(darray *arr, size_t new_capacity);
void add_element(darray *arr, void* element);
void free_darray(darray *arr);
void* get_element(darray *arr, int index);
void* pop_element(darray *arr, int index);
