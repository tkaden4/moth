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

typedef struct moth_insn_s {
    mos_code_t code;
    mos_arg_t args[2];
} moth_insn_t;

int moth_node_init(moth_node_t *);
int moth_node_free(moth_node_t *);

void moth_node_get_bytes(moth_node_t *, buf_t *);

void moth_node_push(moth_node_t *, mos_insn_t *);
