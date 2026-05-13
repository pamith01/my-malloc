# A Simple Memory Allocator (my_malloc)

## The Why? 
To understand how programs interact with Heap Memory

## The What?
At the core, the malloc function has to request memory
from the OS and keep track of free and used memory chunks.

# Algorithm
First-Fit Algorithm

## High Level Design
There are 5 components:
1. The Block Header
2. Find free space
3. Request memory from OS
4. malloc implementation
5. Free the memory

## Tasks of each component
1. The Block Header: Every chunk in the memory should have this header to provide metadata of the block
    • The size of the block
    • Whether it is free or used
    • The pointer to next block

2. Finding Free Space: When the user asks for memory we first check if there is any existing free block 
   that fits the requested size. This is called first fit algorithm.

3. Requesting Space from the OS: If we don’t find a free block we use sbrk(). This system call moves the "program break" (the end of the heap) effectively to provide more memory.

4. Final Malloc Implementation
    It ties everything together
    Validates the size
    Checks for existing free block
    Requests new space if needed
    Returns pointer to memory after the header

5. Free the memory: Free the memory after use.
Set the free attribute of the memory's block header to 0.

