#pragma once

#include<stdint.h>
#include<stdlib.h>

#include<moth/mos.h>
#include<moth/buf.h>

typedef struct moth_node_s moth_node_t;
typedef struct moth_env_s moth_env_t;
typedef struct moth_s moth_t;

typedef struct moth_node_s {
    buf_t buf;
} moth_node_t;

#define MAX_ARGS 2

typedef struct moth_insn_s {
    mos_code_t code;
    size_t nargs;
    mos_arg_t args[MAX_ARGS];
} moth_insn_t;

#define _NARGS(...) \
    ((size_t)(sizeof((mos_arg_t[]){ __VA_ARGS__ })))

#define MOTH_INSN(code, ...) \
    ((moth_insn_t){ code, _NARGS(__VA_ARGS__), { __VA_ARGS__ } })

int moth_node_init(moth_node_t *);
int moth_node_free(moth_node_t *);

void moth_node_get_bytes(moth_node_t *, buf_t *);

void moth_node_push(moth_node_t *, mos_insn_t *);
