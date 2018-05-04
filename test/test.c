#include<moth/moth.h>
#include<moth/mos.h>

#include"test.h"

int main()
{
    moth_insn_t insn = { MOS_LDA, MODE_IMM, 1, { MOTH_IMM(((uint8_t)0x20)) } };
    moth_node_t node;
    moth_node_init(&node);
    moth_node_push(&node, &insn);

    for(size_t i = 0; i < node.buf._sz; ++i){
        printf("%x\n", (uint8_t)*((char *)node.buf.data + i));
    }

    moth_node_free(&node);
    return 0;
}
