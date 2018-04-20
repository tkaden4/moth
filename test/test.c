#include<moth/moth.h>
#include<moth/mos.h>

#include"test.h"

int main()
{
    mos_insn_t insn = { MOS_SEI, MODE_IMPLIED };
    buf_t buf;
    buf_init(&buf);
    if(mos_as_bytes(&insn, &buf)){
        failwith(1, "couldn't find code");
    }
    for(size_t i = 0; i < buf._sz; ++i){
        printf("%x\n", *((char *)buf.data + i));
    }
    buf_free(&buf);
    return 0;
}
