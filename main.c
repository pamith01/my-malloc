#include <stdio.h>
#include <stddef.h>

/* The Block Header */
typedef struct Block
{
    size_t size;
    int free;
    struct Block* next;
}Block;

#define BLOCK_SIZE sizeof(Block)

/* Find free block in the memory - First Fit Algorithm */
/*
Block A     Block B     Block C     Block D     End
 Used   free 10 bytes    Used        Used      of List
*/
Block* find_free_block(Block** last, size_t size, Block* base)
{
    Block *current = base;
    while (current && !(current->free && current->size >= size))
    {
        *last = current;
        current = current->next;
    }
    return current;
}

/* Request from OS */
Block* request_space(Block* last, size_t size)
{
    Block* block = sbrk(0); //Get the current position
    Block* request = sbrk(size + BLOCK_SIZE);

    if (request == (void *)-1)
    {
        return NULL; // sbrk failed
    }

    if (last) last->next = block;
    block->size = size;
    block->free = 0;
    block->next = NULL;
    return block;
}

/* malloc implementation */

void* base = NULL;

Block* my_malloc(size_t size)
{
    Block* block;
    if (size<=0) return NULL;

    if (!base)
    {
        // first call
        block = request_space(base, size);
        if (!block) return NULL;
        base = block;
    }
    else
    {
        Block* last = base;
        block = find_free_block(&last, size, base);
        if (!block)
        {
            block = request_space(last, size);
            if (!block) return NULL;
        }
        else
        {
            block->free = 0;
        }
    }
    return (block + 1); //pointer to the region after the header

}

/* Testing the implementation */
int main()
{
    return 0;
}