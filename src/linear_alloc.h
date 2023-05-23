#ifndef __LINEAR_ALLOC_H__
#define __LINEAR_ALLOC_H__

#include <stdlib.h>
#include <stdint.h>

typedef struct lac_info {
    size_t head;
    size_t capacity;
    uint8_t *buffer;
} lac_info_t;

lac_info_t lac_init(size_t capacity) {
    uint8_t *buffer;

    if (capacity == 0) {
        return (lac_info_t) {
            .head = 0,
            .capacity = 0,
            .buffer = NULL
        };
    }

    buffer = (uint8_t *) malloc(capacity);
    if (buffer == NULL) {
        abort();
    }

    return (lac_info_t) {
        .head = 0,
        .capacity = capacity,
        .buffer = buffer
    };
}

void * lac_alloc(lac_info_t *li, size_t size) {
    uint8_t *mem;

    if (size + li->head > li->capacity) {
        return NULL;
    }

    mem = li->buffer + li->head;

    li->head += size;

    return mem;
}

void lac_destroy(lac_info_t li) {
    free(li.buffer);
}


#endif /* __LINEAR_ALLOC_H__ */
