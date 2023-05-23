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

void print_arr_info(array_int_t *int_arr) {
   printf("arr size: %zu\n", int_arr->size);
   printf("arr cap: %zu\n", int_arr->capacity);
}

int main(void) {

   alloc_t alloc = {
      .alloc = default_alloc,
      .free = default_free,
   };

   array_int_t *int_arr = array_int_init(10, alloc);

   print_arr_info(int_arr);

   array_int_add_all(&int_arr, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

   print_arr_info(int_arr);

   array_int_add_all(&int_arr, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

   print_arr_info(int_arr);

   array_int_add(&int_arr, 55);

   for (size_t i = 0; i < int_arr->size; ++i) {
      printf("i: %zu, val: %d\n", i, array_int_get(int_arr, i));
   }

   array_int_set(int_arr, 19, 55);

   printf("i: 19, val: %d\n", array_int_get(int_arr, 19));

   int *cur;

   array_for_each(int, cur, int_arr) {
      printf("cur: %d\n", *cur);
   }

   size_t idx = 0;
   array_for_each_i(int, cur, idx, int_arr) {
      printf("i: %zu, cur: %d\n", idx, *cur);
   }


   array_int_destroy(int_arr);

}
