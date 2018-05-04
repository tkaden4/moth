#include<moth/buf.h>

#include<string.h>

#define INITIAL_CAP 10

void buf_init(buf_t *buf)
{
    buf->data = calloc(1, INITIAL_CAP);
    buf->_cap = INITIAL_CAP;
    buf->_sz = 0;
}

void buf_free(buf_t *buf)
{
    free(buf->data);
}

void buf_push(buf_t *buf, const void *data, size_t sz)
{
    if(buf->_sz + sz > buf->_cap){
        buf->_cap = buf->_cap + sz;
        buf->data = realloc(buf->data, buf->_cap);
    }
    memmove(buf->data + buf->_sz, data, sz);
    buf->_sz += sz;
}
