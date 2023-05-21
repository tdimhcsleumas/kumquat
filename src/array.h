#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <stdlib.h>
#include "alloc.h"

/**
 * Generic dynamic array generation
 * 
 * This defines a fairly simple dynamic array implementation
 */
#define ARRAY_INFO(T) array ## T
#define ARRAY_TYPE(T) array_ ## T ## _t 


#define build_array(T)                              \
typedef struct ARRAY_INFO(T) {                         \
    size_t size; \
    size_t capacity; \
    alloc_t allocator; \
} ARRAY_TYPE(T); \
\
ARRAY_TYPE(T)* array_ ## T ## _init(size_t capacity, alloc_t alloc) { \
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
void array_ ## T ## _destroy(ARRAY_TYPE(T)* array) { \
    ac_free(array->allocator, array); \
} 




#endif /* __ARRAY_H__ */