#include "types.h"
#include "mem.h"

// Function to initialize a dynamic array
void init_darray(darray *arr, size_t initial_capacity) {
    arr->array = (int *)mem_alloc(initial_capacity * sizeof(int));
    arr->size = 0;
    arr->capacity = initial_capacity;
}

// Function to resize the dynamic array
void resize_darray(darray *arr, size_t new_capacity) {
    int *new_array = (int *)mem_realloc(arr->array, new_capacity * sizeof(int));
    if (new_array) {
        arr->array = new_array;
        arr->capacity = new_capacity;
    } else {
        printf("Memory allocation failed.\n");
    }
}

// Function to add an element to the dynamic array
void add_element(darray *arr, int element) {
    if (arr->size == arr->capacity) {
        // Double the capacity if the array is full
        resize_darray(arr, arr->capacity * 2);
    }
    arr->array[arr->size] = element;
    arr->size++;
}

// Function to free the dynamic array
void free_darray(darray *arr) {
    mem_free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->capacity = 0;
}
