#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "misc.h"
#include "linear_alloc.h"
#include "vec.h"

int main(void) {

    lac_info_t arena = lac_init(4096);

    printf("head before: %lu\n", arena.head);

    char *a, *b, *c;

    a = lac_alloc(&arena, 15);

    if (!a) {
        puts("alloc failed!");
        abort();
    }

    memcpy(a, "Hello World!", 13);

    b = lac_alloc(&arena, 15);

    memcpy(b, "goodbye world!", 15);

    c = lac_alloc(&arena, 2);
    
    memcpy(c, "a", 2);

    puts(a);
    puts(b);
    puts(c);

    printf("head after: %lu\n", arena.head);

    lac_destroy(arena);

    return 0;
}
