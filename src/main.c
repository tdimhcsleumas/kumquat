#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "alloc.h"
#include "vec.h"

void * default_alloc(__UNUSED void *priv, size_t size) {
    return malloc(size);
}

void default_free(__UNUSED void *priv, void *mem) {
    free(mem);
}

typedef struct test {
    int a;
    int b;
} test_t;

int main(void) {

    alloc_t alloc = {
        .alloc = default_alloc,
        .free = default_free,
    };

    vec(int) arr = vec_init(int, 10, alloc);

    for (size_t i = 0; i < 10; ++i) {
        vec_push(&arr, (int)i);
    }

    vec_push(&arr, 12);

    int *cur;
    vec_for_each(cur, arr) {
        printf("%d\n", *cur);
    }

    size_t i;
    vec_for_each_i(cur, i, arr) {
        printf("%zu: %d\n", i, *cur);
    }

    printf("vec_size: %lu\n", vec_size(arr));

    printf("vec_get: %d\n", vec_get(arr, 2));

    vec_set(arr, 2, 99);

    printf("get after set: %d\n", vec_get(arr, 2));

    vec_free(arr);

    vec(test_t) test_arr = vec_init(test_t, 10, alloc);

    vec_push(&test_arr, ((test_t) {
        .a = 1,
        .b = 2
    }));

    test_t *cur_test;
    vec_for_each(cur_test, test_arr) {
        printf("a: %d, b: %d\n", cur_test->a, cur_test->b);
    }

    vec_free(test_arr);

    return 0;
}
