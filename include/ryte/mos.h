#pragma once

#include<stdint.h>
#include<stdlib.h>

typedef enum mos_mode_e {
    MODE_IMM,
    MODE_ZPG,
    MODE_ZPGX,
    MODE_ABS,
    MODE_ABSX,
    MODE_ABSY,
    MODE_INDX,
    MODE_INDY,
    MODE_IMPLIED
} addr_mode_t;

typedef enum mos_code_e {
    adc,
    sdc,
} code_t;

typedef struct mos_insn_s {
    code_t code;
    addr_mode_t mode;
} mos_insn_t;

enum {
    /* buffer too small */
    EMOS_CONV_BUF,
    /* mode/code mismatch (DNE) */
    EMOS_MODE_MIS
};

int mos_from_bytes(mos_insn_t *, uint8_t *, size_t);
int mos_as_bytes(mos_insn_t *, uint8_t **, size_t *);
