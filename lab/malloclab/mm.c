/*
 * mm-naive.c - The fastest, least memory-efficient malloc package.
 * 
 * In this naive approach, a block is allocated by simply incrementing
 * the brk pointer.  A block is pure payload. There are no headers or
 * footers.  Blocks are never coalesced or reused. Realloc is
 * implemented directly using mm_malloc and mm_free.
 *
 * NOTE TO STUDENTS: Replace this header comment with your own header
 * comment that gives a high level description of your solution.
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <string.h>

#include "mm.h"
#include "memlib.h"

/*********************************************************
 * NOTE TO STUDENTS: Before you do anything else, please
 * provide your team information in the following struct.
 ********************************************************/
team_t team = {
    /* Team name */
    "ateam",
    /* First member's full name */
    "Harry Bovik",
    /* First member's email address */
    "bovik@cs.cmu.edu",
    /* Second member's full name (leave blank if none) */
    "",
    /* Second member's email address (leave blank if none) */
    ""
};

/* single word (4) or double word (8) alignment */
#define ALIGNMENT 8

/* rounds up to the nearest multiple of ALIGNMENT */
#define ALIGN(size) (((size) + (ALIGNMENT-1)) & ~0x7)

#define SIZE_T_SIZE (ALIGN(sizeof(size_t)))

#define CHUNK_SIZE (1<<12)

#define WORD_SIZE 4
#define DWORD_SIZE 8
#define META_SIZE DWORD_SIZE

#define GET_WORD(p) (*(unsigned int*)(p))
#define GET_BLOCK_SIZE(h) (GET_WORD(h) & ~0x7)
#define GET_BLOCK_ALLOCATED(p) (GET_WORD(p) & 0x1)

#define GET_HEADER(p) ((void*)(p) - WORD_SIZE)
#define GET_FOOTER_H(h) ((void*)(h) + GET_BLOCK_SIZE(h) - WORD_SIZE)
#define GET_FOOTER(p) (GET_FOOTER_H(GET_HEADER(p)))

#define NEXT_HEADER(h) ((h) + GET_BLOCK_SIZE(h))
#define NEXT_FOOTER(h) (NEXT_HEADER(h) + GET_BLOCK_SIZE(NEXT_HEADER(h)) - WORD_SIZE)
#define PREV_FOOTER(h) ((void*)h - WORD_SIZE)
#define PREV_HEADER(h) ((void*)h - GET_BLOCK_SIZE(PREV_FOOTER(h)))
#define IS_END_HEADER(h) (GET_WORD(h) == 0)

#define GET_PREV_ALLOCATED(p) (GET_BLOCK_ALLOCATED((char*)p - WORD_SIZE))

#define SET_WORD(p, val) (GET_WORD(p)=(val))

#define PACK(size, allocated) ((size) | (allocated))

static void *listHead = NULL;
static void *lastPtr = NULL;

static void *coalesce(void *p) {
    void *header = GET_HEADER(p);
    if (GET_BLOCK_ALLOCATED(header)) return NULL;
    
    int prevAvailable = !GET_BLOCK_ALLOCATED(PREV_FOOTER(header));
    int nextAvailable = !IS_END_HEADER(NEXT_HEADER(header)) && !GET_BLOCK_ALLOCATED(NEXT_HEADER(header));
    
    size_t pSize = GET_BLOCK_SIZE(header);
    if (!prevAvailable && !nextAvailable) {
        return p;
    }
    if (prevAvailable && !nextAvailable) {
        size_t prevSize = GET_BLOCK_SIZE(PREV_FOOTER(header));
        size_t newSize = prevSize + pSize;
        SET_WORD(PREV_HEADER(header), PACK(newSize, 0));
        SET_WORD(GET_FOOTER(p), PACK(newSize, 0));
        return PREV_HEADER(header) + WORD_SIZE;
    }
    // if (!prevAvailable && nextAvailable) {
    //     size_t nextSize = GET_BLOCK_SIZE(NEXT_HEADER(header));
    //     size_t newSize = nextSize + pSize;
    //     SET_WORD(header, PACK(newSize, 0));
    //     SET_WORD(NEXT_FOOTER(header), PACK(newSize, 0));
    //     return p;
    // }
    if (prevAvailable && nextAvailable) {
        size_t prevSize = GET_BLOCK_SIZE(PREV_FOOTER(header));
        size_t nextSize = GET_BLOCK_SIZE(NEXT_HEADER(header));
        size_t newSize = prevSize + pSize + nextSize;
        SET_WORD(PREV_HEADER(header), PACK(newSize, 0));
        SET_WORD(NEXT_FOOTER(header), PACK(newSize, 0));
        return PREV_HEADER(header) + WORD_SIZE;
    }
    return p;
}

static void *extend_heap(size_t s) {
    size_t size = s % 2 ? (s+1) * WORD_SIZE : s * WORD_SIZE;
    void *oldBrk = mem_sbrk(size);
    if ((long)oldBrk == -1) return NULL;

    SET_WORD(oldBrk-WORD_SIZE, PACK(size, 0));
    SET_WORD(oldBrk+size-DWORD_SIZE, PACK(size, 0));
    SET_WORD(oldBrk+size-WORD_SIZE, 0);    
    return coalesce(oldBrk);
}

static int allocate(void *head, size_t blockSize) {
    if (GET_BLOCK_ALLOCATED(head)) return -1;
    size_t emptySize = GET_BLOCK_SIZE(head);
    if (emptySize < blockSize) return -1;
    if (emptySize - blockSize <= META_SIZE) return -1;
    
    size_t leftSize = emptySize - blockSize;
    SET_WORD(head, PACK(blockSize, 1));
    SET_WORD(head+blockSize-WORD_SIZE, PACK(blockSize, 1));
    SET_WORD(head+blockSize, PACK(leftSize, 0));
    SET_WORD(head+emptySize-WORD_SIZE, PACK(leftSize, 0));
    return 0;
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    void *oldBrk = mem_sbrk(WORD_SIZE * 4);
    if (oldBrk == NULL) return -1;
    
    SET_WORD(oldBrk, 0);
    SET_WORD(oldBrk + WORD_SIZE, PACK(META_SIZE, 1));
    SET_WORD(oldBrk + WORD_SIZE * 2, PACK(META_SIZE, 1));
    SET_WORD(oldBrk + WORD_SIZE * 3, 0);
    
    if (extend_heap(CHUNK_SIZE / WORD_SIZE) == NULL) {
        return -1;
    }
    listHead = oldBrk + WORD_SIZE;
    return 0;
}

static void *find_fit(size_t size) {
    void *p = NEXT_HEADER(listHead);
    size_t minSize = -1;
    size_t s;
    void *fit = NULL;
    while (!IS_END_HEADER(p))
    {
        if (!GET_BLOCK_ALLOCATED(p) && (s = GET_BLOCK_SIZE(p)) >= size) {
            if (s < minSize) {
                minSize = s;
                fit = p;
            }
        }
        p = NEXT_HEADER(p);
    }
    return fit;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    size_t newsize = ALIGN(size + META_SIZE);
    void *p = find_fit(newsize);
    if (p == NULL) {
        size_t extendSize = CHUNK_SIZE * (newsize / CHUNK_SIZE + 1);
        p = extend_heap(extendSize);
        if (p != NULL) {
            allocate(p - WORD_SIZE, newsize);
            //assert(p == lastPtr);
            lastPtr = p;
            return p;
        } else {
            return NULL;
        }
    } else {
        size_t emptyBlockSize = GET_BLOCK_SIZE(p);
        if (emptyBlockSize - newsize <= META_SIZE) {
            newsize = emptyBlockSize;
            SET_WORD(p, PACK(newsize, 1));
            SET_WORD(p+newsize-WORD_SIZE, PACK(newsize, 1));
        } else {
            allocate(p, newsize);
        }
        
        lastPtr = p + WORD_SIZE;
        return p + WORD_SIZE;
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
    if (ptr == NULL) return;
    void *header = GET_HEADER(ptr);
    SET_WORD(header, PACK(GET_BLOCK_SIZE(header), 0));
    SET_WORD(GET_FOOTER_H(header), PACK(GET_BLOCK_SIZE(header), 0));
    coalesce(ptr);
}

/*
 * mm_realloc - Implemented simply in terms of mm_malloc and mm_free
 */
void *mm_realloc(void *ptr, size_t size)
{
    void *oldptr = ptr;
    void *newptr;
    size_t copySize;
    
    newptr = mm_malloc(size);
    if (newptr == NULL)
      return NULL;
    copySize = GET_BLOCK_SIZE(GET_HEADER(oldptr));
    if (size < copySize)
      copySize = size;
    memcpy(newptr, oldptr, copySize);
    mm_free(oldptr);
    return newptr;
}