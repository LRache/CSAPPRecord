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
#define GET_HEADER(p) (GET_WORD((char*)(p) - WORD_SIZE))
#define GET_BLOCK_SIZE(p) (GET_WORD(p) & ~0x7)
#define GET_BLOCK_ALLOCATED(p) (GET_WORD(p) & 0x1)
#define GET_FOOTER(p) (GET_WORD((char*)(p) + GET_BLOCK_SIZE(p) - DOUBLE_WORD_SIZE))
#define NEXT_HEADER(p) (GET_BLOCK_SIZE(GET_HEADER(p))+(p)-WORD_SIZE)
#define IS_END(p) (GET_WORD(p) == 0)

#define SET_WORD(p, val) (GET_WORD(p)=val)

#define PACK(size, allocated) ((size) | (allocated))

static void *head = NULL;

static void *extend_heap(size_t s) {
    size_t size = s % 2 ? (s+1) * WORD_SIZE : s * WORD_SIZE;
    char *p = mem_sbrk(size);
    if ((long)p == -1) return NULL;

    SET_WORD(p, PACK(size, 0));
    SET_WORD(p+size-WORD_SIZE, PACK(size, 0));
    SET_WORD(p+size, 0);

    return p;
}

/* 
 * mm_init - initialize the malloc package.
 */
int mm_init(void)
{
    void *oldBrk = mem_sbrk(4*WORD_SIZE);
    if (oldBrk == NULL) return -1;
    SET_WORD(oldBrk, 0);
    SET_WORD(oldBrk + WORD_SIZE, PACK(DWORD_SIZE, 1));
    SET_WORD(oldBrk + WORD_SIZE * 2, PACK(DWORD_SIZE, 1));
    SET_WORD(oldBrk + WORD_SIZE * 3, 0);
    if (extend_heap(CHUNK_SIZE / WORD_SIZE) == NULL) {
        return -1;
    }
    head = oldBrk + DWORD_SIZE;
    return 0;
}

/* 
 * mm_malloc - Allocate a block by incrementing the brk pointer.
 *     Always allocate a block whose size is a multiple of the alignment.
 */
void *mm_malloc(size_t size)
{
    int newsize = ALIGN(size + META_SIZE);
    void *p = NEXT_HEADER(head);
    while (!IS_END(p))
    {
        if (!GET_BLOCK_ALLOCATED(p) && GET_BLOCK_SIZE(p) <= newsize) {
            break;
        }
        p = NEXT_HEADER(p);
    }
    if (IS_END(p)) {
        return extend_heap(newsize);
    } else {
        SET_WORD(p, PACK(newsize, 1));
        SET_WORD(p+newsize-WORD_SIZE, PACK(newsize, 1));
        return p+WORD_SIZE;
    }
}

/*
 * mm_free - Freeing a block does nothing.
 */
void mm_free(void *ptr)
{
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
