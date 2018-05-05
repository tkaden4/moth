#include<moth/moth.h>
#include<moth/mos.h>

#include"test.h"

int main()
{
    moth_insn_t insn = MOTH_INSN(MOS_LDA, MODE_IMM, MOTH_IMM(((uint8_t)0x20)));
    buf_t buf;
    buf_init(&buf);
    moth_translate(&insn, &buf);

    for(size_t i = 0; i < buf._sz; ++i){
        printf("%x\n", (uint8_t)*((char *)buf.data + i));
    }

    buf_free(&buf);
    return 0;
}
