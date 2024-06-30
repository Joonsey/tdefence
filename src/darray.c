#include "types.h"
#include "mem.h"
#include "defines.h"
#include <string.h>

// Function to initialize a dynamic array
void init_darray(Darray *arr, size_t initial_capacity, size_t size) {
    arr->array = (void *)mem_alloc(initial_capacity * size);
	memset(arr->array, 0, initial_capacity * size);
    arr->size = 0;
    arr->capacity = initial_capacity;
	arr->element_size = size;
}

// Function to resize the dynamic array
void resize_darray(Darray *arr, size_t new_capacity) {
    void *new_array = (void *)mem_realloc(arr->array, new_capacity * arr->element_size );
    if (new_array) {
        arr->array = new_array;
        arr->capacity = new_capacity;
    } else {
        printf("Memory allocation failed.\n");
    }
}

// Function to add an element to the dynamic array
void add_element(Darray *arr, void* element) {
    if (arr->size == arr->capacity) {
        resize_darray(arr, arr->capacity * 2);
    }
	mem_copy(arr->array + arr->size * arr->element_size, element, arr->element_size);
	arr->size++;
}

// Function to free the dynamic array
void free_darray(Darray *arr) {
    mem_free(arr->array);
    arr->array = NULL;
    arr->size = 0;
    arr->capacity = 0;
    arr->element_size = 0;
}

void* get_element(const Darray *arr, int index)
{
	if (index >= arr->size | index < 0)
	{
		PRINT_DEBUG("ERROR: index out of bounds");
		return arr->array + arr->size * arr->element_size;
	}
	return arr->array + index * arr->element_size;
}

void* pop_element(Darray *arr, int index)
{
	if (index >= arr->size | index < 0)
	{
		PRINT_DEBUG("ERROR: index out of bounds");
		return NULL;
	}
	void* element = mem_alloc(arr->element_size);
	void* src_ptr = arr->array + index * arr->element_size;
	void* dest_ptr = src_ptr + arr->element_size;

	mem_copy(element, src_ptr, arr->element_size);
	mem_copy(src_ptr, dest_ptr, arr->element_size * (arr->size - index));
	arr->size--;

	return element;
}
