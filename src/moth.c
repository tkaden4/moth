#include<moth/moth.h>

int moth_node_init(moth_node_t *node)
{
    buf_init(&node->buf);
    return 0;
}

int moth_node_free(moth_node_t *node)
{
    buf_free(&node->buf);
    return 0;
}

void moth_node_push(moth_node_t *node, const moth_insn_t *insn)
{
    mos_as_bytes(&insn->insn, &node->buf);
    for(size_t i = 0; i < insn->nargs; ++i){
        const moth_arg_t *arg = &insn->args[i];
        switch(arg->type){
        case MOTH_MEM:
            buf_push(&node->buf, &arg->u.m.addr, arg->u.m.sz);
            break;
        case MOTH_IMM:
            buf_push(&node->buf, &arg->u.imm.imm, arg->u.imm.sz);
            break;
        default:
            fatal("unknown argument type %d", arg->type);
        };
    }
}

void moth_node_write_raw(moth_node_t *node, void *data, size_t sz)
{
    buf_push(&node->buf, data, sz);
}

void moth_node_get_bytes(moth_node_t *node, buf_t *buf)
{
    for(size_t i = 0; i < node->buf._sz; ++i){
        buf_push(buf, node->buf.data + i, sizeof(uint8_t));
    }
}
