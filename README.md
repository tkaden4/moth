# Moth

Moth is a library for generating MOS 6502 bytecode.

### Example
```C
#include<moth/moth.h>
#include<moth/mos.h>

moth_t inst;
moth_init(&inst);

moth_node_t node;
moth_node_new(&base_node(inst), &node);

moth_arg_t arg = MOS_IMM(0xff);
moth_push(&node, MOS_LDA, &arg);

moth_free(&inst);
```
