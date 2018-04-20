#include<moth/mos.h>

typedef struct op_def_s {
    mos_code_t code;
    mos_mode_t mode;
    uint8_t byte;
} op_def_t;

#define bits(aaa, bbb, cc) (((aaa) << 4) | ((bbb) << 2) | (cc))

#define defop(op, mode, code) { op, mode, code }

/* cc = 00 */

#define cc0(op, mode, aaa, bbb) \
    defop(op, mode, bits(aaa, bbb, 0b01))

#define cc0_0(op, aaa) \
    cc0(op, MODE_IMM,    aaa, 0b000), \
    cc0(op, MODE_ZPG,     aaa, 0b001), \
    cc0(op, MODE_ABS,    aaa, 0b010)

/* cc = 01 */

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

/* cc = 10 */

#define cc10(op, mode, aaa, bbb) \
    defop(op, mode, bits(aaa, bbb, 0b10))

#define cc10_stx(op, aaa) \
    cc10(op, MODE_ZPG, aaa, 0b001), \
    cc10(op, MODE_ABS, aaa, 0b011), \
    cc10(op, MODE_ZPGY, aaa, 0b101)

#define cc10_ldx(op, aaa) \
    cc10_stx(op, aaa), \
    cc10(op, MODE_ABSY, aaa, 0b111)

#define cc10_base(op, aaa) \
    cc10(op, MODE_ZPG, aaa, 0b001), \
    cc10(op, MODE_ABS, aaa, 0b011), \
    cc10(op, MODE_ZPGX, aaa, 0b101)

#define cc10_ext(op, aaa) \
    cc10_base(op, aaa), \
    cc10(op, MODE_ABSX, aaa, 0b111)

#define cc10_full(op, aaa) \
    cc10_ext(op, aaa), \
    cc10(op, MODE_A, aaa, 0b010)

#define defbr(br, code) defop(br, MODE_REL, code)
#define defimp(op, code) defop(op, MODE_IMPLIED, code)
#define def08(op, u) defop(op, MODE_IMPLIED, (u << 4) | 0x08)
#define def0A(op, u) defop(op, MODE_IMPLIED, (u << 4) | 0x0A)

static op_def_t defs[] = {
    /* exceptions */
    defimp(MOS_BRK, 0x00),
    defimp(MOS_RTI, 0x40),
    defimp(MOS_RTS, 0x60),
    defop(MOS_JSR, MODE_ABS, 0x20),
    defop(MOS_JMP, MODE_IND, 0x6C),
    defbr(MOS_BPL, 0x10),
    defbr(MOS_BMI, 0x30),
    defbr(MOS_BVC, 0x50),
    defbr(MOS_BVS, 0x70),
    defbr(MOS_BCC, 0x90),
    defbr(MOS_BCS, 0x80),
    defbr(MOS_BNE, 0xD0),
    defbr(MOS_BEQ, 0xF0),
    /* '08' opcodes */
    def08(MOS_PHP, 0x0),
    def08(MOS_CLC, 0x1),
    def08(MOS_PLP, 0x2),
    def08(MOS_SEC, 0x3),
    def08(MOS_PHA, 0x4),
    def08(MOS_CLI, 0x5),
    def08(MOS_PLA, 0x6),
    def08(MOS_SEI, 0x7),
    def08(MOS_DEY, 0x8),
    def08(MOS_TYA, 0x9),
    def08(MOS_TAY, 0xA),
    def08(MOS_CLV, 0xB),
    def08(MOS_INY, 0xC),
    def08(MOS_CLD, 0xD),
    def08(MOS_INX, 0xE),
    def08(MOS_SED, 0xF),
    /* '0A' opcodes */
    def0A(MOS_TXA, 0x8),
    def0A(MOS_TXS, 0x9),
    def0A(MOS_TAX, 0xA),
    def0A(MOS_TSX, 0xB),
    def0A(MOS_DEX, 0xC),
    def0A(MOS_NOP, 0xE),
    /* cc = 00 */
    cc0_0(MOS_CPX, 0b111),
    cc0_0(MOS_CPY, 0b110),
    /* LDY */
    cc0_0(MOS_LDY, 0b101),
    cc0(MOS_LDY, MODE_ZPGX, 0b110, 0b101),
    cc0(MOS_LDY, MODE_ABSX, 0b110, 0b011),
    /* STY */
    cc0(MOS_STY, MODE_ZPG, 0b100, 0b001),
    cc0(MOS_STY, MODE_ABS, 0b100, 0b011),
    cc0(MOS_STY, MODE_ZPGX, 0b100, 0b101),
    /* JMP */
    cc0(MOS_JMP, MODE_ABS, 0b010, 0b101),
    /* BIT */
    cc0(MOS_BIT, MODE_ZPG, 0b001, 0b001),
    cc0(MOS_BIT, MODE_ABS, 0b001, 0b011),
    /* cc = 01 */
    cc1_all(MOS_ORA, 0b000),
    cc1_all(MOS_AND, 0b001),
    cc1_all(MOS_EOR, 0b010),
    cc1_all(MOS_ADC, 0b011),
    cc1_sta(MOS_STA, 0b100),
    cc1_all(MOS_LDA, 0b101),
    cc1_all(MOS_CMP, 0b110),
    cc1_all(MOS_SBC, 0b111),
    /* cc = 10 */
    /* generic */
    cc10_full(MOS_ASL, 0b000),
    cc10_full(MOS_ROL, 0b001),
    cc10_full(MOS_LSR, 0b010),
    cc10_full(MOS_ROR, 0b011),
    /* STX */
    cc10_stx(MOS_STX, 0b100),
    /* LDX */
    cc10_ldx(MOS_LDX, 0b101),
    cc10(MOS_LDX, MODE_IMM, 0b101, 0b000),
    /* DEC */
    cc10_ext(MOS_DEC, 0b110),
    /* INC */
    cc10_ext(MOS_INC, 0b111)
};

#include<stdio.h>

static int op_as_byte(mos_code_t code, mos_mode_t mode, uint8_t *res)
{
    for(size_t i = 0; i < sizeof(defs)/sizeof(defs[0]); ++i){
        if(defs[i].code == code && defs[i].mode == mode){
            *res = defs[i].byte;
            return 0;
        }
    }
    return 1;
}

int mos_as_bytes(const mos_insn_t *insn, buf_t *buf)
{
    uint8_t op_byte;
    if(op_as_byte(insn->code, insn->mode, &op_byte)){
        return 1;
    }
    buf_push(buf, &op_byte, 1);
    return 0;
}
