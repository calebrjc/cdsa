#include "pyramid/dynamic_array.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Calculate the address of the i'th element in dynamic array a.
#define DA_PTR_FROM_IDX(a, i) ((a)->data + ((i) * (a)->elem_size))

/// @brief A structure containing information about a particular dynamic array.
struct da_ctx {
    size_t size;
    size_t capacity;
    size_t elem_size;
    char *data;
};

/// @brief Reallocate the memory associated with a dynamic array.
/// @param da The dynamic array to be reallocated.
/// @param new_capacity The new capacity of the dynamic array.
static void da_realloc(dynamic_array *da, size_t new_capacity) {
    assert(da);

    da->capacity = new_capacity;
    da->data     = (char *)realloc(da->data, da->capacity * da->elem_size);
}

dynamic_array *da_create(size_t elem_size) {
    if (!elem_size) return NULL;

    dynamic_array *da = (dynamic_array *)malloc(sizeof(dynamic_array));
    if (!da) return NULL;

    da->size      = 0;
    da->capacity  = 0;
    da->elem_size = elem_size;
    da->data      = NULL;

    return da;
}

dynamic_array *da_create_n(size_t elem_size, size_t n, const void *initial_value) {
    if (!elem_size) return NULL;

    dynamic_array *da = da_create(elem_size);
    if (!da) return NULL;
    if (!n) return da;

    da_realloc(da, n);
    da->size = n;

    if (initial_value) {
        for (size_t i = 0; i < n; i++) {
            memcpy(DA_PTR_FROM_IDX(da, i), initial_value, da->elem_size);
        }
    }

    return da;
}

dynamic_array *da_dup(const dynamic_array *other) {
    if (!other) return NULL;

    dynamic_array *da = da_create(other->elem_size);
    if (!da) return NULL;

    da_reserve(da, other->capacity);
    da->size = other->size;
    memcpy(da->data, other->data, other->size * other->elem_size);

    return da;
}

void da_destroy(dynamic_array *da) {
    if (!da) return;

    if (da->data) free(da->data);

    free(da);
}

void *da_get(const dynamic_array *da, size_t i) {
    if (da_is_empty(da) || i >= da->size) return NULL;

    return DA_PTR_FROM_IDX(da, i);
}

void da_set(dynamic_array *da, size_t i, const void *elem) {
    if (da_is_empty(da) || i >= da->size || !elem) return;

    memcpy(DA_PTR_FROM_IDX(da, i), elem, da->elem_size);
}

void da_insert(dynamic_array *da, size_t i, const void *elem) {
    if (!da || i > da->size || !elem) return;

    if (da->size == da->capacity) da_realloc(da, (da->capacity) ? da->capacity * 2 : 1);

    // Shift all elements after i to the right by one.
    char *dest = DA_PTR_FROM_IDX(da, i);
    memmove(dest + da->elem_size, dest, (da->size - i) * da->elem_size);

    // Insert the new element.
    memmove(dest, elem, da->elem_size);
    da->size++;
}

void da_erase(dynamic_array *da, size_t i, void *o_elem) {
    if (da_is_empty(da) || i >= da->size) return;

    if (o_elem) memmove(o_elem, da_get(da, i), da->elem_size);

    // Shift all elements after i to the left by one.
    char *dest = DA_PTR_FROM_IDX(da, i);
    memmove(dest, dest + da->elem_size, (da->size - i - 1) * da->elem_size);

    da->size--;
}

void da_push(dynamic_array *da, const void *elem) {
    if (!da || !elem) return;

    if (da->size == da->capacity) da_realloc(da, (da->capacity) ? da->capacity * 2 : 1);

    char *dest = DA_PTR_FROM_IDX(da, da->size);
    memmove(dest, elem, da->elem_size);
    da->size++;
}

void da_pop(dynamic_array *da, void *o_elem) {
    if (da_is_empty(da)) return;

    void *popped = da_back(da);
    da->size--;
    if (o_elem) memmove(o_elem, popped, da->elem_size);
}

void da_clear(dynamic_array *da) {
    if (!da) return;

    da->size = 0;
}

void da_resize(dynamic_array *da, size_t n, const void *initial_value) {
    if (!da) return;

    if (n > da->capacity) da_realloc(da, n);

    if (n > da->size) {
        for (size_t i = da->size; i < n; i++) {
            memcpy(DA_PTR_FROM_IDX(da, i), initial_value, da->elem_size);
        }
    }

    da->size = n;
}

void da_reserve(dynamic_array *da, size_t n) {
    if (!da) return;

    if (n > da->capacity) da_realloc(da, n);
}

void *da_front(const dynamic_array *da) {
    if (da_is_empty(da)) return NULL;

    return da_get(da, 0);
}

void *da_back(const dynamic_array *da) {
    if (da_is_empty(da)) return NULL;

    return da_get(da, da->size - 1);
}

void *da_data(const dynamic_array *da) {
    return da ? (void *)da->data : NULL;
}

bool da_is_empty(const dynamic_array *da) {
    return da ? (da->size == 0) : true;
}

size_t da_size(const dynamic_array *da) {
    return da ? da->size : 0;
}

size_t da_capacity(const dynamic_array *da) {
    return da ? da->capacity : 0;
}
