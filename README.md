# Moth

Moth is a library for generating MOS 6502 bytecode, removing the
need for translation logic in compilers and assemblers.

## Usage
Discrete units of code are encapsulated via `moth_node_t`s.
All operations work on these.

### Using Nodes
Node usage is akin to the following:
```C
moth_node_t node;
moth_node_init(&node);
// ...
moth_node_free(&node);
```

### Using Opcodes
```C
moth_node_t node;
// init code ...
moth_insn_t op = MOTH_INSN(MOS_LDA, MOTH_IMM(0xff));
moth_node_push(&node, &op);
// ...
```

### Getting the bytes
```C
moth_node_t node;
// ...
buf_t buf;
buf_init(&buf);
moth_node_get_bytes(&node, &buf);
// ...
```
