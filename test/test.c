#include<moth/moth.h>
#include<moth/mos.h>

#include"test.h"

int main()
{
    mos_insn_t insn = { MOS_ADC, MODE_IMPLIED };
    if(mos_as_bytes(&insn, NULL)){
        failwith(1, "couldn't find code");
    }
    return 0;
}
