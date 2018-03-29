#pragma once

#include<stdlib.h>

/* dynamically growable buffers */

typedef struct buf_s {
    void *data;
    size_t _sz;
    size_t _cap;
} buf_t;

void buf_init(buf_t *);
void buf_free(buf_t *);

void buf_insert(buf_t *, size_t, void *, size_t);
void buf_delete(buf_t *, size_t, size_t);

void buf_push(buf_t *, void *, size_t);
void buf_pop(buf_t *, size_t);
