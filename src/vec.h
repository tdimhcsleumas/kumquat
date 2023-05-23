/**
 * vec.h 
 * 
 * vec(T) -- macro type of the vec
 * 
 * vec_init(T, len, alloc)
 * 
 * vec_free(mem)
 * 
 * vec_push()
 * 
 * vec_pop()
 * 
 * vec_get()
 * 
 * vec_set()
 * 
 */
#ifndef __VEC_H_
#define __VEC_H_

#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "alloc.h"

typedef struct vec_info {
    size_t size;
    size_t capacity;
    size_t element_size;
    alloc_t allocator;
} vec_info_t;

vec_info_t * _vec_init(size_t capacity, size_t element_size, alloc_t alloc) {
    vec_info_t *vec_info = ac_malloc(alloc, (capacity * element_size) + sizeof(vec_info_t));
    if (!vec_info) {
        return NULL;
    }

    *vec_info = (vec_info_t) {
        .size = 0,
        .capacity = capacity,
        .element_size = element_size,
        .allocator = alloc
    };

    return vec_info + 1;
}

void vec_free(void *mem) {
    vec_info_t *vec_info = ((vec_info_t *) mem) - 1;

    ac_free(vec_info->allocator, vec_info);
}

void vec_ensure_size(void **arr) {
    vec_info_t **vec_info_p = (vec_info_t **) arr;
    vec_info_t *vec_info = (*vec_info_p) - 1, *new_vec_info;
    size_t new_capacity;

    if (vec_info->size < vec_info->capacity) return;

    new_capacity = vec_info->capacity + 30;

    new_vec_info = ac_malloc(vec_info->allocator, (vec_info->element_size * new_capacity) + sizeof(vec_info_t));

    if (new_vec_info == NULL) {
        abort();
    }

    memcpy(new_vec_info + 1, vec_info + 1, vec_info->element_size * vec_info->capacity);

    *new_vec_info = (vec_info_t) {
        .size = vec_info->size,
        .capacity = new_capacity,
        .element_size = vec_info->element_size,
        .allocator = vec_info->allocator
    };

    ac_free(vec_info->allocator, vec_info);

    *vec_info_p = new_vec_info + 1;
}

int abort_exit() {
    abort();
    return 0;
}

#define vec(T) T *

#define vec_init(T, len, alloc) (T*)(_vec_init(len, sizeof(T), alloc))

#define vec_size(arr) (((vec_info_t *) (arr)) - 1)->size

#define vec_push(arrp, val) vec_ensure_size((void *)(arrp)); \
    (*arrp)[vec_size(*arrp)++] = (val)

#define vec_for_each(cur, arr) \
    for(cur = arr; cur != arr + vec_size(arr); ++cur)

#define vec_for_each_i(cur, i, arr)                                 \
    for (i = 0, cur = arr; cur != arr + vec_size(arr); ++cur, ++i)

#define vec_assert_in_bounds(arr, idx) ((idx) < vec_size(arr) ? (idx) : abort_exit())

#define vec_get(arr, idx) (arr[vec_assert_in_bounds(arr, idx)])

#define vec_set(arr, idx, val) \
    (vec_get(arr, idx)) = (val)

#endif /* __VEC_H_ */
