#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include "alloc.h"

/**
 * Generic dynamic array generation
 * 
 * This defines a fairly simple dynamic array implementation
 */
#define ARRAY_INFO(T) array_ ## T
#define ARRAY_TYPE(T) array_ ## T ## _t 


#define build_array(T)                              \
typedef struct ARRAY_INFO(T) {                         \
    size_t size; \
    size_t capacity; \
    alloc_t allocator; \
} ARRAY_TYPE(T); \
\
ARRAY_TYPE(T)* array_ ## T ## _init(size_t capacity, alloc_t alloc) \
{ /** This will create a dynamic array with an initial capacity. Capcity may be 0 */ \
    ARRAY_TYPE(T) *array_info = ac_malloc(alloc, (capacity * sizeof(T)) + sizeof(ARRAY_TYPE(T))); \
    if (!array_info) { \
        return NULL; \
    } \
    \
    \
    *array_info = (ARRAY_TYPE(T)) { \
        .size = 0, \
        .capacity = capacity, \
        .allocator = alloc \
    }; \
    \
    return array_info; \
} \
\
void array_ ## T ## _destroy(ARRAY_TYPE(T)* array) \
{ /** frees memory associated with the array */ \
    ac_free(array->allocator, array); \
} \
void array_ ## T ## _assert_bounds(ARRAY_TYPE(T)* array, size_t idx) \
{ \
    if (idx >= array->size) { \
        fprintf(stderr, "Attempted to read array out of bounds.\n"); \
        abort(); \
    } \
} \
\
\
void array_ ## T ## _ensure_capacity(ARRAY_TYPE(T)** array_p, size_t count) \
{ /** This function ensures that we are able to accomodate the requested number of arguments */ \
    ARRAY_TYPE(T) *array = *array_p, *new_array; \
    size_t new_capacity; \
    \
    if (array->size + count <= array->capacity) return; \
    \
    new_capacity = array->size + count; \
    new_array = ac_malloc(array->allocator, (new_capacity * sizeof(T)) + sizeof(ARRAY_TYPE(T))); \
    \
    if (new_array == NULL) abort(); \
    \
    memcpy(new_array, array, (array->capacity * sizeof(T)) + sizeof(ARRAY_TYPE(T))); \
    \
    *new_array = (ARRAY_TYPE(T)) { \
        .size = array->size, \
        .capacity = new_capacity, \
        .allocator = array->allocator \
    }; \
    \
    ac_free(array->allocator, array); \
    \
    *array_p = new_array; \
} \
\
void array_ ## T ## _add_all(ARRAY_TYPE(T)** array_p, size_t count, ...) \
{ /** Add all count variables to the end of the array */ \
    va_list ap; \
    va_start(ap, count); \
    array_ ## T ## _ensure_capacity(array_p, count); \
    ARRAY_TYPE(T) *array = *array_p; \
    \
    for (size_t i = 0; i < count; ++i) { \
        ((T*)(array + 1))[array->size++] = va_arg(ap, T); \
    } \
    \
    va_end(ap); \
} \
\
T array_ ## T ## _get(ARRAY_TYPE(T)* array, size_t idx) \
{ /** get the item associated with idx. if out of range, abort */ \
    array_ ## T ## _assert_bounds(array, idx); \
    return ((T*)(array + 1))[idx]; \
} \
\
void array_ ## T ## _set(ARRAY_TYPE(T)* array, size_t idx, T val) \
{ \
    array_ ## T ## _assert_bounds(array, idx); \
    ((T*)(array + 1))[idx] = val; \
}

/** unfortunately, these need to be loosely typed macros */
#define array_for_each(T, cur, arr) \
    for(cur = (T*)(arr + 1); cur != ((T*)(arr + 1)) + arr->size; ++cur)

#define array_for_each_i(T, cur, i, arr)                                 \
    for (i = 0, cur = (T*)(arr + 1); cur != ((T*)(arr + 1)) + arr->size; ++cur, ++i)

#endif /* __ARRAY_H__ */
