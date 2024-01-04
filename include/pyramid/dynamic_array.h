#include <stdbool.h>
#include <stddef.h>

/// @brief A dynamic array structure with functionality that resembles a C++ vector.
typedef struct da_ctx dynamic_array;

/// @brief Return an allocated dynamic array structure which can store elements of size elem_size,
/// or NULL if no such dynamic array can be allocated.
/// @param elem_size The size of the structures being stored by this dynamic array.
/// @return An allocated dynamic array structure which can store elements of size elem_size, or NULL
/// if no such dynamic array can be allocated.
dynamic_array *da_create(size_t elem_size);

/// @brief Return an allocated dynamic array structure with n elements, each initialized to the
/// object pointed to by initial_value, or NULL if no such dynamic array can be allocated. When n is
/// zero, this function behaves identically to da_create.
/// @param elem_size The size of the structures being stored by this dynamic array.
/// @param n The number of elements to be stored within the dynamic array.
/// @param initial_value A pointer to the object to be used as the initial value for each element
/// within the dynamic array. If NULL, the associated memory is allocated, but left uninitialized.
/// @return An allocated dynamic array structure with n elements, each initialized to the object
/// pointed to by initial_value, or NULL if no such dynamic array can be allocated.
dynamic_array *da_create_n(size_t elem_size, size_t n, const void *initial_value);

/// @brief Return an allocated dynamic array structure with the same contents as other, or NULL if
/// no such dynamic array can be allocated.
/// @param other The dynamic array to be duplicated.
/// @return An allocated dynamic array structure with the same contents as other, or NULL if no such
/// dynamic array can be allocated.
dynamic_array *da_dup(const dynamic_array *other);

/// @brief Release the memory associated with a dynamic array.
/// @param da The dynamic array to be destroyed.
void da_destroy(dynamic_array *da);

/// @brief Return a pointer to the element within the dynamic array at index i, or NULL if no such
/// element can be obtained.
/// @param da The dynamic array to be accessed.
/// @param i The index of the element to be retreived.
/// @return A pointer to the element within the dynamic array at index i, or NULL if no such element
/// can be obtained.
void *da_get(const dynamic_array *da, size_t i);

/// @brief Overwrite the element at index i with elem. Has no effect if i is out of bounds or elem
/// is NULL.
/// @param da The dynamic array to be modified.
/// @param i The index to overwrite.
/// @param elem The element to overwrite the existing one with.
void da_set(dynamic_array *da, size_t i, const void *elem);

/// @brief Insert the structure pointed to by elem at index i. Has no effect if i is out of bounds
/// or elem is NULL.
/// @param da The dynamic array to be modified.
/// @param i The index at which to insert the element.
/// @param elem The element to insert into the dynamic array.
void da_insert(dynamic_array *da, size_t i, const void *elem);

/// @brief Erase the element at index i and, if o_elem is non-null, copy it into o_elem.
/// @param da The dynamic array to be modified.
/// @param i The index of the element to be erased.
/// @param o_elem If not null, the element that is removed from the dynamic array. The memory
/// pointed to by o_elem should be allocated by the caller.
void da_erase(dynamic_array *da, size_t i, void *o_elem);

/// @brief Push an element onto the end of the dynamic array.
/// @param da The dynamic array to be modified.
/// @param elem The element to add to the dynamic array.
void da_push(dynamic_array *da, const void *elem);

/// @brief Pop an element from the end of the dynamic array and, if o_elem is non-null, copy it into
/// o_elem.
/// @param da The dynamic array to be modified.
/// @param o_elem If not null, the element that is removed from the dynamic array.
void da_pop(dynamic_array *da, void *o_elem);

/// @brief Erase all elements from the dynamic array.
/// @param da The dynamic array to be modified.
void da_clear(dynamic_array *da);

/// @brief Resize the dynamic array to contain n elements, with each element past the original size
/// initialized to the object pointed to by initial_value.
/// @param da The dynamic array to be modified.
/// @param n The number of elements to be stored within the dynamic array.
/// @param initial_value A pointer to the object to be used as the initial value for each new
/// element within the dynamic array.
void da_resize(dynamic_array *da, size_t n, const void *initial_value);

/// @brief Reserve storage for at least n elements within the dynamic array.
/// @param da The dynamic array to be modified.
/// @param n The number of elements to reserve storage for within the dynamic array.
void da_reserve(dynamic_array *da, size_t n);

/// @brief Return a pointer to the element at the front of the dynamic array, or NULL if no such
/// element can be obtained.
/// @param da The dynamic array to be accessed.
/// @return A pointer to the element at the front of the dynamic array, or NULL if no such element
/// can be obtained.
void *da_front(const dynamic_array *da);

/// @brief Return a pointer to the element at the back of the dynamic array, or NULL if no such
/// element can be obtained.
/// @param da The dynamic array to be accessed.
/// @return A pointer to the element at the back of the dynamic array, or NULL if no such element
/// can be obtained.
void *da_back(const dynamic_array *da);

/// @brief Return true if the dynamic array contains no elements, and false otherwise.
/// @param da The dynamic array to be checked.
/// @return True if the dynamic array contains no elements, and false otherwise.
bool da_is_empty(const dynamic_array *da);

/// @brief Return the number of elements currently stored within the dynamic array.
/// @param da The dynamic array to be checked.
/// @return The number of elements currently stored within the dynamic array.
size_t da_size(const dynamic_array *da);

/// @brief Return the number of elements that can be stored within the dynamic array before the next
/// reallocation occurs.
/// @param da The dynamic array to be checked.
/// @return The number of elements that can be stored within the dynamic array before the next
/// reallocation occurs.
size_t da_capacity(const dynamic_array *da);

/// @brief Return the underlying array used as storage for the dynamic array, or NULL if no such
/// storage exists.
/// @param da The dynamic array to be accessed.
/// @return The underlying array used as storage for the dynamic array, or NULL if no such storage
/// exists.
void *da_data(const dynamic_array *da);

#if 0

typedef void (*da_print_function)(void *, char **);

void da_print(dynamic_array *da, da_print_function pf);

#endif
