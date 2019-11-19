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

void *base = NULL;

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

t_block get_block(void *p)
{
    char *tmp;
    tmp = p;
    return (p = tmp -= BLOCK_SIZE);
}

int valid_addr(void *p)
{
    if (base)
    {
        if (p > base && p < sbrk(0))
        {
            return (p == (get_block(p))->ptr);
        }
    }
    return 0;
}

t_block find_block(t_block *last, size_t size)
{
    t_block b = base;
    while (b && !(b->free && b->size >= size))
    {
        *last = b;
        b = b->next;
    }
    return (b);
}


t_block extend_heap(t_block last, size_t s)
{
    t_block b;
    b = sbrk(0);
    if (sbrk(BLOCK_SIZE + s) == (void*) -1)
        return NULL;

    b->size = s;
    b->next = NULL;
    b->prev = last;
    b->ptr = b->data;

    if (last)
        last->next = b;

    b->free = 0;
    return b;
}


void split_block(t_block b, size_t s)
{
    t_block new;
    new = (t_block)(b->data + s);
    new->size = b->size - s - BLOCK_SIZE;
    new->next = b->next;
    new->prev = b;
    new->free = 1;
    new->ptr = new->data;
    b->size = s;
    b->next = new;
    if (new->next)
        new->next->prev = new;
}

t_block fusion(t_block b)
{
    if (b->next && b->next->free)
    {
        b->size += BLOCK_SIZE + b->next->size;
        b->next = b->next->next;
        if (b->next)
            b->next->prev = b;
    }
    return b;
}

void free(void *p)
{
    t_block b;
    if (valid_addr(p))
    {
        b = get_block(p);
        b->free = 1;
        /* fusion with previous if possible */
        if (b->prev && b->prev->free)
            b = fusion(b->prev);
        /* then fusion with next */
        if (b->next)
            fusion(b);
        else
        {
            /* free the end of the heap */
            if (b->prev)
                b->prev->next = NULL;
            else
                /* No more block !*/
                base = NULL;
            brk(b);
        }
    }
}


void *malloc(size_t size)
{
    t_block b, last;
    size_t s;
#ifdef ENV32BIT
    s = align4(size);
#elif defined(ENV64BIT)
    s = align8(size);
#endif
    if (base)
    {
        /* First find a block */
        last = base;
        b = find_block(&last, s);
        if (b)
        {
            /* can we split */
            if ((b->size - s) >= (BLOCK_SIZE + 4))
                split_block(b, s);
            b->free = 0;
        }
        else
        {
            /* No fitting block , extend the heap */
            b = extend_heap(last, s);
            if (!b)
                return NULL;
        }
    }
    else
    {
        /* first time */
        b = extend_heap(NULL, s);
        if (!b)
            return NULL;
        base = b;
    }
    return b->data;
}