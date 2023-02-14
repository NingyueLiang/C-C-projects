/*
 ******************************************************************************
 *                               mm.c                                         *
 *           64-bit struct-based implicit free list memory allocator          *
 *                      without coalesce functionality                        *
 *                 CSE 361: Introduction to Computer Systems                  *
 *                                                                            *
 *  ************************************************************************  *
 *                     insert your documentation here. :)                     *
 *                                                                            *
 *  ************************************************************************  *
 *  ** ADVICE FOR STUDENTS. **                                                *
 *  Step 0: Please read the writeup!                                          *
 *  Step 1: Write your heap checker. Write. Heap. checker.                    *
 *  Step 2: Place your contracts / debugging assert statements.               *
 *  Good luck, and have fun!                                                  *
 *                                                                            *
 ******************************************************************************
 */

/* Do not change the following! */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <assert.h>
#include <stddef.h>

#include "mm.h"
#include "memlib.h"

#ifdef DRIVER
/* create aliases for driver tests */
#define malloc mm_malloc
#define free mm_free
#define realloc mm_realloc
#define calloc mm_calloc
#endif /* def DRIVER */

/* You can change anything from here onward */

/*
 * If DEBUG is defined, enable printing on dbg_printf and contracts.
 * Debugging macros, with names beginning "dbg_" are allowed.
 * You may not define any other macros having arguments.
 */
// #define DEBUG // uncomment this line to enable debugging

#ifdef DEBUG
/* When debugging is enabled, these form aliases to useful functions */
#define dbg_printf(...) printf(__VA_ARGS__)
#define dbg_requires(...) assert(__VA_ARGS__)
#define dbg_assert(...) assert(__VA_ARGS__)
#define dbg_ensures(...) assert(__VA_ARGS__)
#else
/* When debugging is disnabled, no code gets generated for these */
#define dbg_printf(...)
#define dbg_requires(...)
#define dbg_assert(...)
#define dbg_ensures(...)
#endif

/* Basic constants */
typedef uint64_t word_t;
static const size_t wsize = sizeof(word_t);   // word and header size (bytes)
static const size_t dsize = 2*sizeof(word_t);       // double word size (bytes)
static const size_t min_block_size = 4*sizeof(word_t); // Minimum block size
static const size_t chunksize = (1 << 12);    // requires (chunksize % 16 == 0) (mark)
//the bit shows if the block is allocated
static const word_t alloc_mask = 0x1;
//the bit shows if the previous block is allocated
static const word_t prev_free_mask = 0x2;
//the bits shows if the size of the block
static const word_t size_mask = ~(word_t)0xF;

typedef struct block
{
    /* Header contains size + allocation flag */
    word_t header;
    /*modify the struct to store explicit list pointers when freed block*/
    union{
        struct{
            struct block* prev;
            struct block* next;
        };

    /*
     * We don't know how big the payload will be.  Declaring it as an
     * array of size 0 allows computing its starting address using
     * pointer notation.
     */
        char payload[0];
    };
    /*
     * We can't declare the footer as part of the struct, since its starting
     * position is unknown
     */
} block_t;


/* Global variables */
/* Pointer to first block */
static block_t *heap_start = NULL;

static int n_fits = 10;
static block_t *root = NULL;
bool mm_checkheap(int lineno);

/* Function prototypes for internal helper routines */
static block_t *extend_heap(size_t size);
static void place(block_t *block, size_t asize);
static block_t *find_fit(size_t asize);
static block_t *coalesce(block_t *block);

static size_t max(size_t x, size_t y);
static size_t round_up(size_t size, size_t n);
static word_t pack(size_t size, bool alloc, bool prev);

static size_t extract_size(word_t header);
static size_t get_size(block_t *block);
static size_t get_payload_size(block_t *block);

static bool extract_alloc(word_t header);
static bool get_alloc(block_t *block);

static void write_header(block_t *block, size_t size, bool alloc, bool prev);
static void write_footer(block_t *block, size_t size, bool alloc, bool prev);

static block_t *payload_to_header(void *bp);
static void *header_to_payload(block_t *block);

static block_t *find_next(block_t *block);
static word_t *find_prev_footer(block_t *block);
static block_t *find_prev(block_t *block);
static bool get_prev_alloc(block_t *block);
static void print_heap(void);
void free_list_insert(block_t* block);
void free_list_remove(block_t* block);
/*
 * The mm_init intialize the heap as well as headers of segregated free lists
 */
bool mm_init(void) 
{
    // Create the initial empty heap 
    word_t *start = (word_t *)(mem_sbrk(2*wsize));

    if (start == (void *)-1) 
    {
        return false;
    }

    start[0] = pack(0, true, true); // Prologue footer
    start[1] = pack(0, true, true); // Epilogue header
    root = NULL;
    // Heap starts with first "block header", currently the epilogue footer
    heap_start = (block_t *) &(start[1]);
    
    // Extend the empty heap with a free block of chunksize bytes
    if (extend_heap(chunksize) == NULL)
    {
        return false;
    }
    dbg_requires(mm_checkheap(__LINE__));
    mm_checkheap(__LINE__);
    return true;
}

/*
 * malloc takes in an argument of size and require to allocated a block
 * of at least size bytes from free area in the heap to hold "size"
 * byte data.
 */
void *malloc(size_t size) 
{
    dbg_requires(mm_checkheap(__LINE__));
    //mm_checkheap(__LINE__);
    size_t asize;      // Adjusted block size
    size_t extendsize; // Amount to extend heap if no fit is found
    block_t *block;    //pointer to the block
    void *bp = NULL;

    if (heap_start == NULL) // Initialize heap if it isn't initialized
    {   
        mm_init();
    }

    if (size == 0) // Ignore spurious request
    {
        dbg_ensures(mm_checkheap(__LINE__));
        return bp;
    }

    // Adjust block size to include overhead and to meet alignment requirements
    // remove footer and only require sqace for header
    asize = round_up(size + wsize, dsize);
    if(asize < min_block_size){  //for a 16 bytes block, 8 bytes is for data
        asize = min_block_size;  //decrease the minimum block size to 16 byte (next step)
    } 

    // Search the free list for a fit
    block = find_fit(asize);

    // If no fit is found, request more memory, and then and place the block
    if (block == NULL)
    {  
        extendsize = max(asize, chunksize);
        block = extend_heap(extendsize);
        if (block == NULL) // extend_heap returns an error
        {
            return bp;
        }

    }

    place(block, asize);
    bp = header_to_payload(block);
    //check heap
    dbg_ensures(mm_checkheap(__LINE__));
    return bp;
} 

/*
 * The free function will free the block at the point bp,
 * change the block's allocation, call coalesce, and 
 * add to the free lists at last.
 */
void free(void *bp)
{   
    dbg_requires(mm_checkheap(__LINE__));
    //mm_checkheap(__LINE__);
    //just return when free a null pointer bp
    if (bp == NULL)
    { 
        return;
    }
   
    //get the payload from the block pointer
    block_t *block = payload_to_header(bp); 
    //get the size of the block
    size_t size = get_size(block);
    //get the allocated status of the prev block
    bool prev = get_prev_alloc(block);

    //write header & footer
    write_header(block, size, false, prev);
    write_footer(block, size, false, prev);

    //change the allocation state of this block in the next 
    //block's header
    // block_t *next = find_next(block);
    // size_t n_size = get_size(next);
    // bool n_alloc = get_alloc(next);
    // write_header(next, n_size, n_alloc, false);
    // if(!n_alloc){ //if the next block is free, write the footer
    //     write_footer(next, n_size, n_alloc, false);
    // }
    coalesce(block);
    dbg_requires(mm_checkheap(__LINE__));
}

/*
 * realloc takes in an argument of size and require to allocated a block
 * of at least size bytes from free area in the heap to hold "size"
 * byte data that copy from the payload at ptr.
 */
void *realloc(void *ptr, size_t size)
{
    //get the block with the ptr
    block_t *block = payload_to_header(ptr);
    size_t copysize;
    void *newptr;

    // If size == 0, then free block and return NULL
    if (size == 0)
    {
        free(ptr);
        return NULL;
    }

    // If ptr is NULL, then equivalent to malloc
    if (ptr == NULL)
    {
        return malloc(size);
    }
     
    // Otherwise, proceed with reallocation
    newptr = malloc(size);
    // If malloc fails, the original block is left untouched
    if (newptr == NULL)
    {
        return NULL;
    }

    // Copy the old data
    copysize = get_payload_size(block); // gets size of old payload
    if(size < copysize)
    {
        copysize = size;
    }
    memcpy(newptr, ptr, copysize);

    // Free the old block
    free(ptr);

    return newptr;
}

/*
 * calloc takes in arguments of elements & size and require to allocated a block
 * of at least size bytes from free area in the heap to hold "elements*size"
 * byte data. 
 */
void *calloc(size_t elements, size_t size)
{
    void *bp;
    //total size of memory that has to be allocated
    size_t asize = elements * size;

    if (asize/elements != size)
    {    
        // Multiplication overflowed
        return NULL;
    }
    
    bp = malloc(asize);
    if (bp == NULL)
    {
        return NULL;
    }
    // Initialize all bits to 0
    memset(bp, 0, asize);

    return bp;
}

/******** The remaining content below are helper and debug routines ********/

/*
 * The extend heap function will extend the heap 
 */
static block_t *extend_heap(size_t size) 
{
    void *bp;

    // Allocate an even number of words to maintain alignment
    size = round_up(size, dsize);
    if ((bp = mem_sbrk(size)) == (void *)-1)
    {
        return NULL;
    }
    
    // Initialize free block header/footer 
    block_t *block = payload_to_header(bp);
    //get prev allocation state and write the hearder&footer for new block
    bool prev = get_prev_alloc(block);
    write_header(block, size, false, prev);
    write_footer(block, size, false, prev);
    // Create new epilogue header
    block_t *block_next = find_next(block);
    write_header(block_next, 0, true, false);

    // Coalesce in case the previous block was free
    return coalesce(block);
}

/*
 * The coalesce function will combine the previous/next blocks together with
 * this block if they are freed.
 */
static block_t *coalesce(block_t * block) 
{   
    //intialize the new size & pointer of the new block
    size_t new_size = get_size(block);
    block_t* new = block;
    //divide the situation into several cases
    //get the pointer of next block
    block_t* next = find_next(block);
    //get the size & allocated information of next block;
    size_t size_next = get_size(next);
    bool alloc_next = get_alloc(next);
    
    //get the allocated information of previous block;
    bool alloc_prev = get_prev_alloc(block);
   
    //if prev is freed, coalesce with the prev block
    if(!alloc_prev){ 
         //get the pointer of previous block
        block_t* prev = find_prev(block);
        //get the size & allocated information of previous block;
        if(prev != block){
            size_t size_prev = get_size(prev);
            new = prev;
            new_size += size_prev;
            free_list_remove(prev);
        }
       

    }

    if(!alloc_next){ //if next is freed, coalesce with the next block
        new_size += size_next;
        free_list_remove(next);
    }

    write_header(new,new_size,false, true);
    write_footer(new,new_size,false, true);
    free_list_insert(new);
    //update the next block's prev_allocated state
    block_t *new_next = find_next(new);
    size_t next_size = get_size(new_next);
    write_header(new_next, next_size, true, false);
    return new;
}

/*
 * The place function will decide that whether we have to 
 * separate the block into two blocks, insert one into the free list 
 * after asize bytes of space in the block is occupied.
 */
static void place(block_t *block, size_t asize)
{
    size_t csize = get_size(block);// get the current size of the block
    // if enough space for separate
    if ((csize - asize) >= min_block_size)
    {   
        
        block_t *next_block;
        //separate to get the first block which is allocated
        free_list_remove(block);
        write_header(block, asize, true, get_prev_alloc(block));
        
        //separate to get the second block which is freed
        next_block = find_next(block);
        free_list_insert(next_block);
        write_header(next_block, csize-asize, false, true);
        write_footer(next_block, csize-asize, false, true);
    }

    else
    {   
        free_list_remove(block);
        write_header(block, csize, true, get_prev_alloc(block));
        //update the next block's prev_allocated state
        block_t *next_block = find_next(block);
        size_t next_size = get_size(next_block);
        bool next_alloc = get_alloc(next_block);
        write_header(next_block,next_size, next_alloc, true);
        if(!next_alloc){ //if next block is freed
            write_footer(next_block, next_size, next_alloc, true);
        }

    }
}

/*
 * The fit function will find the best fit block of asize to 
 * allocated from free lists and return that.
 */
static block_t *find_fit(size_t asize)
{
    block_t *block;
    block_t *n_fit_block = NULL;
    int fits = 0;
    for (block = root; (block != NULL) && (fits < n_fits); block = block->next)
    {
        if (!(get_alloc(block)) && (asize <= get_size(block)))
        {
            fits++;
            if(n_fit_block == NULL){
                n_fit_block = block;
            }else if(get_size(block)<get_size(n_fit_block)){
                n_fit_block = block;
            }
        }
    }
    return n_fit_block; 
   
}
/* 
 * The mm_cheackheap will check the heap invariant by iterating 
 * through heap & free lists to make sure there're no bugs.
 * Please keep modularity in mind when you're writing the heap checker!
 */
bool mm_checkheap(int line)  
{ 
    print_heap(); 
    return true;
}

static void print_heap(void)
{
    block_t *bp;
    for (bp = heap_start; get_size(bp) != 0; bp = find_next(bp))
    {
        printf("%p:\tsize: %lu\talloc: %d\tprev_alloc: %d", bp, get_size(bp), get_alloc(bp), get_prev_alloc(bp));

        if (get_alloc(bp)){
            printf("\n");
        }else{
            if (!get_prev_alloc(bp))
                printf("\tnext: %p\tprev: %p\n", find_next(bp), find_prev(bp));
            else
                printf("\tnext: %p\n", find_next(bp));
        }
    }
    
}
/*
    free_list_insert: insert a block into the explicit free list at the beginning; return void.
*/
void free_list_insert(block_t* block)
{
    if(block == NULL){
        return;
    }else if(root == NULL){
        root = block;
        block->prev = NULL;
        block->next = NULL;
        return;
    }else{
        block->next = root;
        block->prev = NULL;
        root->prev = block;
        root = block;
        return;
    }
}

/*
    free_list_remove: remove a block from the explicit free list; return void.
*/

void free_list_remove(block_t* block)
{
    if(block == NULL){
        return;
    }
    if(block == root){
        root = block->next;
    }
    if(block->prev != NULL){
        block->prev->next = block->next;
    }
    if(block->next != NULL){
        block->next->prev = block->prev;
    }
    return;
}

/*
 * max: returns x if x > y, and y otherwise.
 */
static size_t max(size_t x, size_t y)
{
    return (x > y) ? x : y;
}

/*
 * round_up: Rounds size up to next multiple of n
 */
static size_t round_up(size_t size, size_t n)
{
    return (n * ((size + (n-1)) / n));
}

/*
 * pack: returns a header reflecting a specified size and its alloc status.
 *       If the block is allocated, the lowest bit is set to 1, and 0 otherwise.
 */
static word_t pack(size_t size, bool alloc, bool prev)
{
    word_t tmp = alloc ? (size | alloc_mask) : size;
    return prev ? (tmp | prev_free_mask) : tmp;
}


/*
 * extract_size: returns the size of a given header value based on the header
 *               specification above.
 */
static size_t extract_size(word_t word)
{
    return (word & size_mask);
}

/*
 * get_size: returns the size of a given block by clearing the lowest 4 bits
 *           (as the heap is 16-byte aligned).
 */
static size_t get_size(block_t *block)
{
    return extract_size(block->header);
}

/*
 * get_payload_size: returns the payload size of a given block, equal to
 *                   the entire block size minus the header and footer sizes.
 */
static word_t get_payload_size(block_t *block)
{
    size_t asize = get_size(block);
    return asize - wsize;
}

/*
 * extract_alloc: returns the allocation status of a given header value based
 *                on the header specification above.
 */
static bool extract_alloc(word_t word)
{
    return (bool)(word & alloc_mask);
}

/*
 * get_alloc: returns true when the block is allocated based on the
 *            block header's lowest bit, and false otherwise.
 */
static bool get_alloc(block_t *block)
{
    return extract_alloc(block->header);
}

/*
 * extract_alloc: returns the previous allocation status of a given 
 * header value based on the header specification above.
 */
static bool extract_prev_alloc(word_t word)
{
    return (bool)(word & prev_free_mask);
}

/*
 * get_alloc: returns true when the previous block is allocated based on the
 *            block header's 2nd lowest bit, and false otherwise.
 */
static bool get_prev_alloc(block_t *block)
{
    return extract_prev_alloc(block->header);
}

/*
 * write_header: given a block and its size and allocation status,
 *               writes an appropriate value to the block header.
 */
static void write_header(block_t *block, size_t size, bool alloc, bool prev)
{
    block->header = pack(size, alloc, prev);
}


/*
 * write_footer: given a block and its size and allocation status,
 *               writes an appropriate value to the block footer by first
 *               computing the position of the footer.
 */
static void write_footer(block_t *block, size_t size, bool alloc, bool prev)
{
    word_t *footerp = (word_t *)((block->payload) + get_size(block) - dsize);
    *footerp = pack(size, false, prev);
}


/*
 * find_next: returns the next consecutive block on the heap by adding the
 *            size of the block.
 */
static block_t *find_next(block_t *block)
{
    dbg_requires(block != NULL);
    
    block_t *block_next = (block_t *)(((char *)block) + get_size(block));

    dbg_ensures(block_next != NULL);
    return block_next;
}

/*
 * find_prev_footer: returns the footer of the previous block.
 */
static word_t *find_prev_footer(block_t *block)
{
    // Compute previous footer position as one word before the header
    if (get_prev_alloc(block)){
        printf("The prev block is allocated");
        exit(-1);
    }
    return (&(block->header)) - 1;
}

/*
 * find_prev: returns the previous block position by checking the previous
 *            block's footer and calculating the start of the previous block
 *            based on its size.
 */
static block_t *find_prev(block_t *block)
{
    word_t *footerp = find_prev_footer(block);
    size_t size = extract_size(*footerp);
     if (size == 0){
        size = wsize;
     }
    return (block_t *)((char *)block - size);
}

/*
 * payload_to_header: given a payload pointer, returns a pointer to the
 *                    corresponding block.
 */
static block_t *payload_to_header(void *bp)
{
    return (block_t *)(((char *)bp) - offsetof(block_t, payload));
}

/*
 * header_to_payload: given a block pointer, returns a pointer to the
 *                    corresponding payload.
 */
static void *header_to_payload(block_t *block)
{
    return (void *)(block->payload);
}
