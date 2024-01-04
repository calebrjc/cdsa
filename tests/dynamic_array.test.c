#include "pyramid/dynamic_array.h"

#include <criterion/criterion.h>
#include <criterion/logging.h>

Test(dynamic_array, create) {
    // da_create() should return a valid dynamic array.
    dynamic_array *arr = da_create(sizeof(size_t));

    cr_assert_not_null(arr);
    cr_assert_eq(da_size(arr), 0);
    cr_assert_eq(da_is_empty(arr), true);
    cr_assert_eq(da_capacity(arr), 0);
    cr_assert_null(da_data(arr));

    da_destroy(arr);

    // da_create() should return NULL if given an element size of 0.
    arr = da_create(0);

    cr_assert_null(arr);

    da_destroy(arr);
}

Test(dynamic_array, create_n) {
    // da_create_n() should return a valid dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    cr_assert_not_null(arr);
    cr_assert_eq(da_size(arr), 10);
    cr_assert_eq(da_is_empty(arr), false);
    cr_assert_geq(da_capacity(arr), 10);
    cr_assert_not_null(da_data(arr));

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);

    // da_create_n() should return NULL if given an element size of 0.
    arr = da_create_n(0, 10, &(size_t){42});

    cr_assert_null(arr);

    da_destroy(arr);

    // da_create_n() should behave like da_create() if given a size of 0.
    arr = da_create_n(sizeof(size_t), 0, &(size_t){42});

    cr_assert_not_null(arr);
    cr_assert_eq(da_size(arr), 0);
    cr_assert_eq(da_is_empty(arr), true);
    cr_assert_eq(da_capacity(arr), 0);
    cr_assert_null(da_data(arr));

    da_destroy(arr);

    // da_create_n() should not return NULL if given a NULL initial value.
    arr = da_create_n(sizeof(size_t), 10, NULL);

    cr_assert_not_null(arr);

    da_destroy(arr);
}

Test(dynamic_array, dup) {
    // da_dup() should return a valid dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    dynamic_array *dup = da_dup(arr);

    cr_assert_not_null(dup);
    cr_assert_eq(da_size(dup), 10);
    cr_assert_eq(da_is_empty(dup), false);
    cr_assert_geq(da_capacity(dup), 10);
    cr_assert_not_null(da_data(dup));

    for (size_t i = 0; i < da_size(dup); i++) cr_assert_eq(*(size_t *)da_get(dup, i), 42);

    da_destroy(arr);
    da_destroy(dup);

    // da_dup() should return NULL if given a NULL dynamic array.
    dup = da_dup(NULL);

    cr_assert_null(dup);

    da_destroy(dup);
}

Test(dynamic_array, get) {
    // da_get() should return a valid element for a valid dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);

    // da_get() should return NULL if given a NULL dynamic array.
    cr_assert_null(da_get(NULL, 0));

    // da_get() should return NULL if given an index that is out of bounds.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    cr_assert_null(da_get(arr, 10));

    da_destroy(arr);
}

Test(dynamic_array, set) {
    // da_set() should overwrite the element at index i with elem.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_set(arr, 0, &(size_t){0});
    da_set(arr, 6, &(size_t){6});
    da_set(arr, da_size(arr) - 1, &(size_t){da_size(arr) - 1});

    cr_assert_eq(da_size(arr), 10);
    cr_assert_eq(*(size_t *)da_get(arr, 0), 0);
    cr_assert_eq(*(size_t *)da_get(arr, 6), 6);
    cr_assert_eq(*(size_t *)da_get(arr, da_size(arr) - 1), da_size(arr) - 1);

    da_destroy(arr);

    // da_set() should do nothing if given a NULL dynamic array.
    da_set(NULL, 0, &(size_t){42});

    // da_set() should do nothing if given an index that is out of bounds.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_set(arr, 10, &(size_t){42});

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);

    // da_set() should do nothing if given a NULL element.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_set(arr, 0, NULL);

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);
}

Test(dynamic_array, insert) {
    // da_insert() should insert the element at index i.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_insert(arr, 5, &(size_t){0});

    cr_assert_eq(da_size(arr), 11);
    cr_assert_eq(*(size_t *)da_get(arr, 5), 0);

    da_destroy(arr);

    // da_insert() should do nothing if given a NULL dynamic array.
    da_insert(NULL, 0, &(size_t){42});

    // da_insert() should do nothing if given an index that is out of bounds.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_insert(arr, 10, &(size_t){42});

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);

    // da_insert() should do nothing if given a NULL element.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_insert(arr, 0, NULL);

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);
}

Test(dynamic_array, erase) {
    // da_erase() should erase the element at index i.
    dynamic_array *arr = da_create(sizeof(size_t));
    cr_assert_not_null(arr);

    for (size_t i = 0; i < 10; i++) da_push(arr, &i);

    size_t erased;
    da_erase(arr, 5, &erased);

    cr_assert_eq(da_size(arr), 9);
    cr_assert_eq(erased, 5);

    da_destroy(arr);

    // da_erase() should do nothing if given a NULL dynamic array.
    da_erase(NULL, 0, &(size_t){42});

    // da_erase() should do nothing if given an index that is out of bounds.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_erase(arr, 10, &(size_t){42});

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);
}

Test(dynamic_array, push) {
    // da_push() should push the element onto the end of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_push(arr, &(size_t){0});

    cr_assert_eq(da_size(arr), 11);
    cr_assert_eq(*(size_t *)da_get(arr, 10), 0);

    da_destroy(arr);

    // da_push() should do nothing if given a NULL dynamic array.
    da_push(NULL, &(size_t){42});

    // da_push() should do nothing if given a NULL element.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_push(arr, NULL);

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);
}

Test(dynamic_array, pop) {
    // da_pop() should pop the element from the end of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    size_t popped;
    da_pop(arr, &popped);

    cr_assert_eq(da_size(arr), 9);
    cr_assert_eq(popped, 42);

    da_destroy(arr);

    // da_pop() should do nothing if given a NULL dynamic array.
    da_pop(NULL, &(size_t){42});

    // da_pop() should do nothing if given a NULL element.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});

    da_pop(arr, NULL);

    for (size_t i = 0; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 42);

    da_destroy(arr);
}

Test(dynamic_array, clear) {
    // da_clear() should clear the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_clear(arr);

    cr_assert_eq(da_size(arr), 0);

    da_destroy(arr);

    // da_clear() should do nothing if given a NULL dynamic array.
    da_clear(NULL);
}

Test(dynamic_array, size) {
    // da_size() should return the size of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    cr_assert_eq(da_size(arr), 10);

    da_destroy(arr);

    // da_size() should return 0 if given a NULL dynamic array.
    cr_assert_eq(da_size(NULL), 0);
}

Test(dynamic_array, is_empty) {
    // da_is_empty() should return true if the dynamic array is empty.
    dynamic_array *arr = da_create(sizeof(size_t));
    cr_assert_not_null(arr);

    cr_assert_eq(da_is_empty(arr), true);

    da_destroy(arr);

    // da_is_empty() should return false if the dynamic array is not empty.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    cr_assert_eq(da_is_empty(arr), false);

    da_destroy(arr);

    // da_is_empty() should return true if given a NULL dynamic array.
    cr_assert_eq(da_is_empty(NULL), true);
}

Test(dynamic_array, capacity) {
    // da_capacity() should return the capacity of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    cr_assert_geq(da_capacity(arr), 10);

    da_destroy(arr);

    // da_capacity() should return 0 if given a NULL dynamic array.
    cr_assert_eq(da_capacity(NULL), 0);
}

Test(dynamic_array, resize) {
    // da_resize() should resize the dynamic array to the given size.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_resize(arr, 20, &(size_t){0});

    cr_assert_eq(da_size(arr), 20);

    for (size_t i = 10; i < da_size(arr); i++) cr_assert_eq(*(size_t *)da_get(arr, i), 0);

    da_destroy(arr);

    // da_resize() should shrink the dynamic array if given a smaller size.
    arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_resize(arr, 5, &(size_t){0});

    cr_assert_eq(da_size(arr), 5);

    da_destroy(arr);

    // da_resize() should do nothing if given a NULL dynamic array.
    da_resize(NULL, 0, &(size_t){42});
}

Test(dynamic_array, reserve) {
    // da_reserve() should reserve storage for the given number of elements.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_reserve(arr, 20);

    cr_assert_geq(da_capacity(arr), 20);

    da_destroy(arr);

    // da_reserve() should do nothing if given a NULL dynamic array.
    da_reserve(NULL, 0);
}

Test(dynamic_array, front) {
    // da_front() should return the front element of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_set(arr, 0, &(size_t){0});
    cr_assert_eq(*(size_t *)da_front(arr), 0);

    da_destroy(arr);

    // da_front() should return NULL if given a NULL dynamic array.
    cr_assert_null(da_front(NULL));

    // da_front() should return NULL if the dynamic array is empty.
    arr = da_create(sizeof(size_t));
    cr_assert_not_null(arr);

    cr_assert_null(da_front(arr));

    da_destroy(arr);
}

Test(dynamic_array, back) {
    // da_back() should return the back element of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    da_set(arr, da_size(arr) - 1, &(size_t){0});
    cr_assert_eq(*(size_t *)da_back(arr), 0);

    da_destroy(arr);

    // da_back() should return NULL if given a NULL dynamic array.
    cr_assert_null(da_back(NULL));

    // da_back() should return NULL if the dynamic array is empty.
    arr = da_create(sizeof(size_t));
    cr_assert_not_null(arr);

    cr_assert_null(da_back(arr));

    da_destroy(arr);
}

Test(dynamic_array, data) {
    // da_data() should return the underlying array of the dynamic array.
    dynamic_array *arr = da_create_n(sizeof(size_t), 10, &(size_t){42});
    cr_assert_not_null(arr);

    cr_assert_not_null(da_data(arr));

    da_destroy(arr);

    // da_data() should return NULL if given a NULL dynamic array.
    cr_assert_null(da_data(NULL));
}
