#include <stdio.h>
#include <assert.h>

#include "malloc_free.c"

int main()
{
    int *ip;

#ifdef ENV64BIT
    printf("pointer size (64bit system): %zu\n", sizeof(ip));

    printf("------------------------------------------\n");
    printf("test1: malloc pointer of size 12 bytes...\n");
    char *test1 = malloc(sizeof(char) * 12);
    printf("pointer address test1: %p\n", (void *)test1);
    free(test1);
    printf("pointer address test1 after free: %p\n", (void *)test1);

    printf("------------------------------------------\n");
    printf("test2: malloc pointer of size 6 bytes...\n");
    char *test2 = malloc(sizeof(char) * 6);
    /* New address should be the same as old since memory was freed */
    assert((void *)test1 == (void *)test2);
    printf("pointer address2: %p\n", (void *)test2);
    printf("test 2 will not be freed...\n");

    printf("------------------------------------------\n");
    printf("test3: malloc pointer of size 6 bytes...\n");
    char *test3 = malloc(sizeof(char) * 6);
    /* New address shouldnt bee the same as the old since last block wasnt freed */
    assert((void *)test2 != (void *)test3);
    printf("pointer address3: %p\n", (void *)test3);
    printf("------------------------------------------\n");
    printf("Reached end of test...\n");
#elif defined(ENV32BIT)
    printf("pointer size (32bit): %zu\n", sizeof(ip));

    printf("------------------------------------------\n");
    printf("test1: malloc pointer of size 12 bytes...\n");
    char *test1 = malloc(sizeof(char) * 12);
    printf("pointer address test1: %p\n", (void *)test1);
    free(test1);
    printf("pointer address test1 after free: %p\n", (void *)test1);

    printf("------------------------------------------\n");
    printf("test2: malloc pointer of size 6 bytes...\n");
    char *test2 = malloc(sizeof(char) * 6);
    /* New address should be the same as old since memory was freed */
    assert((void *)test1 == (void *)test2);
    printf("pointer address2: %p\n", (void *)test2);
    printf("test 2 will not be freed...\n");

    printf("------------------------------------------\n");
    printf("test3: malloc pointer of size 6 bytes...\n");
    char *test3 = malloc(sizeof(char) * 6);
    /* New address shouldnt bee the same as the old since last block wasnt freed */
    assert((void *)test2 != (void *)test3);
    printf("pointer address3: %p\n", (void *)test3);
    printf("------------------------------------------\n");
    printf("Reached end of test...\n");
#endif
}
