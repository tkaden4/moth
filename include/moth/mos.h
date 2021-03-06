#pragma once

#include<stdint.h>
#include<stdlib.h>

#include<moth/buf.h>

typedef enum mos_mode_e {
    MODE_A = 0,
    MODE_IMM,
    MODE_IND,
    MODE_IND_ZPGX,
    MODE_INDZPG_Y,
    MODE_ZPG,
    MODE_ZPGY,
    MODE_ZPGX,
    MODE_ABS,
    MODE_ABSX,
    MODE_ABSY,
    MODE_INDX,
    MODE_INDY,
    MODE_IMPLIED,
    MODE_REL
} mos_mode_t;

typedef enum mos_code_e {
    MOS_ADC = 0,
    MOS_AND,
    MOS_ASL,
    MOS_BCC,
    MOS_BCS,
    MOS_BEQ,
    MOS_BNE,
    MOS_BPL,
    MOS_BIT,
    MOS_BMI,
    MOS_BRK,
    MOS_BVC,
    MOS_BVS,
    MOS_CLC,
    MOS_CLD,
    MOS_CLI,
    MOS_CLV,
    MOS_CMP,
    MOS_CPX,
    MOS_CPY,
    MOS_DEC,
    MOS_DEX,
    MOS_DEY,
    MOS_EOR,
    MOS_INC,
    MOS_INX,
    MOS_INY,
    MOS_JMP,
    MOS_JSR,
    MOS_LDA,
    MOS_LDX,
    MOS_LDY,
    MOS_LSR,
    MOS_NOP,
    MOS_ORA,
    MOS_PHA,
    MOS_PHP,
    MOS_PLA,
    MOS_PLP,
    MOS_ROL,
    MOS_ROR,
    MOS_RTI,
    MOS_RTS,
    MOS_SBC,
    MOS_SEC,
    MOS_SED,
    MOS_SEI,
    MOS_STA,
    MOS_STX,
    MOS_STY,
    MOS_TAX,
    MOS_TAY,
    MOS_TSX,
    MOS_TXA,
    MOS_TXS,
    MOS_TYA,
    MOS_MAX_OP
} mos_code_t;

typedef enum mos_reg_e {
    MOS_A,
    MOS_X,
    MOS_Y
} mos_reg_t;

typedef struct mos_insn_s {
    mos_code_t code;
    mos_mode_t mode;
} mos_insn_t;

typedef enum err {
    MOS_INVALID_MODE = 1,
    MOS_INVALID_OP = 2
} err;

err mos_as_bytes(const mos_insn_t *, buf_t *);
