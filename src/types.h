#pragma once
#include "stdio.h"

typedef struct darray_t {
    void *array;
    size_t  element_size;
    size_t size;
    size_t capacity;
} Darray;

void init_darray(Darray *arr, size_t initial_capacity, size_t size);
void resize_darray(Darray *arr, size_t new_capacity);
void add_element(Darray *arr, void* element);
void free_darray(Darray *arr);
void* get_element(const Darray *arr, int index);
void* pop_element(Darray *arr, int index);
double radians_to_degrees(double radians);
