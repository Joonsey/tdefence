#include "stdio.h"

typedef struct {
    int *array;
    size_t size;
    size_t capacity;
} darray;

void init_darray(darray *arr, size_t initial_capacity);
void resize_darray(darray *arr, size_t new_capacity);
void add_element(darray *arr, int element);
void free_darray(darray *arr);
