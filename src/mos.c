#include<moth/mos.h>

typedef uint32_t flag_t;

/* cc and aaa identify opcode, while bbb determines the opmode */
typedef struct op_bits_s {
    flag_t cc : 2;
    flag_t bbb : 3;
    flag_t aaa : 3;
} op_bits_t;

/* bi-directional translation tree */

typedef struct op_encode_s op_encode_t;
typedef struct mode_encode_s mode_encode_t;

typedef struct mode_encode_s {
    mos_mode_t mode;
    flag_t bbb : 3;
} mode_encode_t; 

typedef struct op_encode_s {
    mos_code_t code;
    /* identifying bits */
    flag_t cc : 2;
    flag_t aaa : 3;
} op_encode_t;

/* cc = 01 mode encoding table */
static mode_encode_t cc01_modes[] = {
    { MODE_IND_ZPGX, 0b000 },
    { MODE_ZPG,      0b001 }
    { MODE_IMM,      0b010 },
    { MODE_ABS,      0b011 },
    { MODE_ZPGY,     0b100 },
    { MODE_ZPGX,     0b101 }
    { MODE_ABSX,     0b110 }
    { MODE_ABSY,     0b111 }
};

/* global translation table */
static op_encode_t encodings[] = {
    /* cc = 0b01 */
    { MOS_ORA, 0b01, 0b000 },
    { MOS_AND, 0b01, 0b001 },
    { MOS_EOR, 0b01, 0b010 },
    { MOS_ADC, 0b01, 0b011 },
    { MOS_STA, 0b01, 0b100 },
    { MOS_LDA, 0b01, 0b101 },
    { MOS_CMP, 0b01, 0b110 },
    { MOS_SBC, 0b01, 0b111 }
};
