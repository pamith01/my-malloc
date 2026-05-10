/* Block Header - stored bore each block */
struct block_meta
{
    size_t size;            // Size of block including header
    struct block_meta *next;// Next free block (only used if free) 
    int free;               // 1 if free, 0 if allocated
};

/* Memory layout after malloc(100) returns: 
[ header (size=108, next=?, free=0) ][ 100 usable bytes for caller ]
                                        ^-- returned pointer points here
*/

void * heap_start = NULL; // First block's header address
struct block_meta *free_list = NULL; //Head of explicit free list 

/* First call to malloc initializes the heap */

/* Phase-1: Getting memory from the OS (helper function) */
void* request_from_os(size_t size)
{
    void* new_memory = sbrk(size);
    if (new_memory == (void*)-1)
    {
        perror("sbrk failed\n");
        return NULL;
    }
    return new_memory;
}

/* Phase-2: Heap Initialization */
// Task: when free list is NULL, initialize heap 
if (free_list == NULL)
{
    // Get initial pool from OS eg. 16KB
    void *pool = request_from_os(16 * 1024);
    if (!pool) return NULL;

    // Create first block header at pool
    struct block_meta *first = (struct block_meta*)pool;
    first->size = 16*1024; //entire pool size 
    first->free = 1;
    first->next = NULL;
    
    // Set free_list to this block
    free_list = first;

/* Phase-3: Free List Search (First-fit) */
// Task: Find the first free block with size>= requested size 

struct block_meta *find_free_block(size_t requested_size)
{
    struct block_meta *current = free_list;

    while(current)
    {
        if (current->free && current->size >= requested_size)
        {
            return current; //Found suitable block 
        }

        current = current->next;
    }
    return NULL; //No block found
}

/* Phase-4: Allocation (Mark block as used)*/
// Task: From the found free block, mark it allocated.
struct block_meta *block = find_free_block(total_size);
if (block)
{
    block->free = 0;
}

//Remove from free list 
//Need to find previous node in free_list to unlink
// traverse again or use doubly linked list 

return (void*)(block + 1); //pointer after the header

}