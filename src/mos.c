#include<moth/mos.h>

typedef struct op_def_s {
    mos_code_t code;
    mos_mode_t mode;
    uint8_t byte;
} op_def_t;

#define bits(aaa, bbb, cc) (((aaa) << 4) | ((bbb) << 2) | (cc))

#define defop(op, mode, code) { op, mode, code }

#define cc1(op, mode, aaa, bbb) \
    defop(op, mode, bits(aaa, bbb, 0b01))

#define cc1_sta(op, aaa) \
    cc1(op, MODE_IND_ZPGX,  aaa, 0b000), \
    cc1(op, MODE_ZPG,       aaa, 0b001), \
    cc1(op, MODE_ABS,       aaa, 0b011), \
    cc1(op, MODE_INDZPG_Y,  aaa, 0b100), \
    cc1(op, MODE_ZPGX,      aaa, 0b101), \
    cc1(op, MODE_ABSY,      aaa, 0b110), \
    cc1(op, MODE_ABSX,      aaa, 0b111) 

#define cc1_all(op, aaa) \
    cc1_sta(op, aaa), \
    cc1(op, MODE_IMM,      aaa, 0b010) 

static op_def_t defs[] = {
    /* exceptions */
    defop(MOS_BRK, MODE_IMPLIED, 0x00),
    defop(MOS_JSR, MODE_ABS, 0x20),
    defop(MOS_RTI, MODE_IMPLIED, 0x40),
    defop(MOS_RTS, MODE_IMPLIED, 0x60),
    defop(MOS_BPL, MODE_REL, 0x10),
    defop(MOS_BMI, MODE_REL, 0x30),
    defop(MOS_BVC, MODE_REL, 0x50),
    defop(MOS_BVS, MODE_REL, 0x70),
    defop(MOS_BCC, MODE_REL, 0x90),
    defop(MOS_BCS, MODE_REL, 0x80),
    defop(MOS_BNE, MODE_REL, 0xD0),
    defop(MOS_BEQ, MODE_REL, 0xF0),
    /* cc = 00 */
    /* cc = 01 */
    cc1_all(MOS_ORA, 0b000),
    cc1_all(MOS_AND, 0b001),
    cc1_all(MOS_EOR, 0b010),
    cc1_all(MOS_ADC, 0b011),
    /* sdc exceptions */
    cc1_sta(MOS_STA, 0b100),
    /******************/
    cc1_all(MOS_LDA, 0b101),
    cc1_all(MOS_CMP, 0b110),
    cc1_all(MOS_SBC, 0b111),
    /* cc = 10 */
};

static int op_as_byte(mos_code_t code, mos_mode_t mode, uint8_t *res)
{
    for(size_t i = 0; i < sizeof(defs); ++i){
        if(defs[i].code == code && defs[i].mode == mode){
            *res = defs[i].byte;
            return 0;
        }
    }
    return 1;
}

int mos_as_bytes(mos_insn_t *insn, buf_t *buf)
{
    (void) buf;
    uint8_t op_byte;
    if(op_as_byte(insn->code, insn->mode, &op_byte)){
        return 1;
    }
    return 0;
}
