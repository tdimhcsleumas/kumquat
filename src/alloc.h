#ifndef __ALLOC_H__
#define __ALLOC_H__

#include <stdlib.h>

typedef struct alloc {
    void *priv;
    void *(*alloc)(void *priv, size_t);
    void (*free)(void *priv, void *mem);
} alloc_t;

void * ac_malloc(alloc_t alc, size_t size) {
    return alc.alloc(alc.priv, size);
}

void ac_free(alloc_t alc, void *mem) {
    alc.free(alc.priv, mem);
}

#endif /* __ALLOC_H__ */