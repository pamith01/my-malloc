# A Simple Memory Allocator (my_malloc)

## The Why? 
To understand how programs interact with Heap Memory

## The What?
At the core, the malloc function has to request memory
from the OS and keep track of free and used memory chunks.

## High Level Design
There are 5 components:
1. The Block Header
2. Find free block 
3. Request memory from OS
4. malloc implementation
5. Free the memory

