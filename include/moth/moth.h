#pragma once

#include<stdint.h>
#include<stdio.h>
#include<stdlib.h>

#include<moth/mos.h>
#include<moth/buf.h>

#define MAX_ARGS 4

#define fatal(fmt, ...) \
    ({ fprintf(stderr, "fatal: " fmt "\n", ##__VA_ARGS__); exit(1); })

typedef struct moth_node_s {
    buf_t buf;
} moth_node_t;

typedef struct moth_arg_s {
    enum {
        MOTH_MEM = 0,
        MOTH_IMM,
        //MOTH_REG
    } type;
    union {
        struct {
            size_t sz;
            uint32_t addr;
        } m;
        struct {
            size_t sz;
            uint32_t imm;
        } imm;
        //mos_reg_t reg;
    } u;
} moth_arg_t; 

typedef struct moth_insn_s {
    mos_insn_t insn;
    size_t nargs;
    moth_arg_t args[MAX_ARGS];
} moth_insn_t;


#define MOTH_MEM(val)\
    { .type = MOTH_MEM, .u = { .m = { .addr = val, .sz = sizeof(typeof(val)) }} }

#define MOTH_IMM(val)\
    { .type = MOTH_IMM, .u = { .imm = { .imm = val, .sz = sizeof(typeof(val)) }} }

#define MOTH_REG(val)\
    { .type = MOTH_IMM, .u = { .reg = val } }

#define _NARGS(type, ...) \
    ((size_t)(sizeof((type[]){ __VA_ARGS__ }))/sizeof(type))

#define MOTH_INSN(code, mode, ...) \
    { { code, mode }, _NARGS(moth_arg_t, __VA_ARGS__), { __VA_ARGS__ } }


int moth_node_init(moth_node_t *);
int moth_node_free(moth_node_t *);

void moth_node_get_bytes(moth_node_t *, buf_t *);

int moth_translate(moth_insn_t *, buf_t *);

void moth_node_push(moth_node_t *, const moth_insn_t *);
