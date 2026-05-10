Custom Malloc Function

What malloc must do?
> Allocate a contiguous block of atleast size bytes
> Return a pointer to start of the block
> The block must be suitably aligned for any data type (typically 8 or 16 bytes)
> Memory should be reusable after free
> On failure, return NULL

The core problem: track free and used memory blocks of memory

Minimal Version - Design choices
> Implicit free list (headers only, no coalescing first)
> sbrk for heap extension
> First-fit search

Then incrementally add coalescing, alignment, footer tags

What the function contains?
- malloc that allocates memory from a growing heap
- free that marks memory as reusable (no coalescing)
- Single-threaded, no thread safety concerns
- Explicit free list
- First-fit allocation
