#ifndef MALLOC_FREE_H
#define MALLOC_FREE_H

#include <sys/types.h>
#include <unistd.h>

#if __GNUC__
#if __x86_64__ || __ppc64__
#define ENV64BIT
#define BLOCK_SIZE 40
#define align8(x) (((x) + 7) & (-8))
#else
#define ENV32BIT
#define BLOCK_SIZE 20
#define align4(x) (((((x)-1) >> 2) << 2) + 4)
#endif
#endif

struct s_block
{
    size_t size;
    struct s_block *next;
    struct s_block *prev;
    int free;
#ifdef ENV64BIT
    int padding;
#endif
    void *ptr; /* A pointer to the allocated block */
    char data[1];
};
typedef struct s_block *t_block;

t_block get_block(void *p);
int valid_addr(void *p);
t_block find_block(t_block *last, size_t size);
t_block extend_heap(t_block last, size_t s);
void split_block(t_block b, size_t s);
t_block fusion(t_block b);
void free(void *p);
void *malloc(size_t size);

#endif