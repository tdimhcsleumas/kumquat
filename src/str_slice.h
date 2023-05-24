#ifndef __STR_SLICE_H__
#define __STR_SLICE_H__

#include <stdlib.h>
#include <string.h>

#include "misc.h"

/**
 * @brief Simple implementation of an immutable, length-based string
 */

typedef struct str_slice {
   const char *str;
   const size_t len;
} str_slice_t;

str_slice_t str_slice_create(char *str, const size_t len) {
   return (str_slice_t) {
      .str = str,
      .len = len,
   };
}

str_slice_t str_slice_create_from_cstr (char *str) {
   const size_t len = strlen(str);
   return (str_slice_t) {
      .str = str,
      .len = len,
   };
}

const size_t str_slice_len(str_slice_t slice) {
   return slice.len;
}

const char * str_slice_mem(str_slice_t slice) {
   return slice.str;
}

str_slice_t str_slice_substr(str_slice_t slice, size_t start, size_t end) {
   const size_t len = min(end, slice.len) - start;

   if (start >= end || start >= slice.len || len == 0) {
      return (str_slice_t) {
         .str = NULL,
         .len = 0
      };
   }

   return (str_slice_t) {
      .str = slice.str + start,
      .len = len
   };
}

#endif /** __STR_SLICE_H__ */
