#pragma once

#include<stdint.h>
#include<stdlib.h>

/*
typedef struct ryte_vtable_s {
    void(*append)(uint8_t, void *);
} ryte_vtable_t;
*/

/* Program context, used for building
 * a complete program */
typedef struct ryte_ctx_s {
    uint8_t *buf;
} ryte_ctx_t;

void ryte_ctx_init(ryte_ctx_t *ctx);
void ryte_ctx_finalize(uint8_t **, size_t *);
void ryte_ctx_destroy(ryte_ctx_t *ctx);
