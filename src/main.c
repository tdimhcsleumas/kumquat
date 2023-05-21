#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "linear_alloc.h"
#include "vec.h"
#include "array.h"

build_array(int)

void * default_alloc(__UNUSED void *priv, size_t size) {
    return malloc(size);
}

void default_free(__UNUSED void *priv, void *mem) {
    free(mem);
}

int main(void) {

    alloc_t alloc = {
        .alloc = default_alloc,
        .free = default_free,
    };

   array_int_t *int_arr = array_int_init(10, alloc);

   printf("arr cap: %zu\n", int_arr->capacity);

   array_int_destroy(int_arr);

}