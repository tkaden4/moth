#pragma once

#include<stdint.h>
#include<stdlib.h>

#include<moth/buf.h>

typedef enum mos_mode_e {
    MODE_A,
    MODE_IMM,
    MODE_IND_ZPGX,
    MODE_ZPG,
    MODE_ZPGY,
    MODE_ZPGX,
    MODE_ABS,
    MODE_ABSX,
    MODE_ABSY,
    MODE_INDX,
    MODE_INDY,
    MODE_IMPLIED
} mos_mode_t;

typedef enum mos_code_e {
    MOS_ORA,
    MOS_AND,
    MOS_EOR,
    MOS_ADC,
    MOS_STA,
    MOS_LDA,
    MOS_CMP,
    MOS_SBC,
} mos_code_t;

typedef struct mos_arg_s {
    enum {
        I8,
        I16,
        I32
    } sz;
    union {
        uint8_t i8;
        uint16_t i16;
        uint32_t i32;
    } u;
} mos_arg_t;

typedef struct mos_insn_s {
    mos_code_t code;
    mos_mode_t mode;
    mos_arg_t *args;
    size_t n_arg;
} mos_insn_t;

int mos_as_bytes(mos_insn_t *, buf_t *);
