#ifndef MALLOC_C
#define MALLOC_C

#include <stdio.h>
#include <stdlib.h>

#include "Malloc.h"

#ifndef BEST_FIT
#ifndef FIRST_FIT
#define FIRST_FIT
#endif
#endif

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "%s:%d: %s is not implemented yet.\n", \
        __FILE__, __LINE__, __func__); \
        abort(); \
    } while (0) \

size_t allocated_size = 0;

size_t chunks_num = 0;

byte *head_ptr = heap;

void *c_malloc(size_t size)
{
    if (size == 0 || size + allocated_size > HEAP_SIZE) {
        return NULL;
    }

#ifdef BEST_FIT
    size_t best_chunk_id = -1;
    size_t best_chunk_size = -1;

    for (size_t i = 0; i < chunks_num; ++i) {
        if (chunks[i].isFree && size <= chunks[i].size) {
            if (best_chunk_id == -1) { //no chunk is selected yet
                best_chunk_id = i;
                best_chunk_size = chunks[i].size;
            } else {
                if (chunks[i].size == size) { // found a chunk exactly suiting the requested size
                    best_chunk_id = i;
                    best_chunk_size = chunks[i].size;
                    break;
                } else if (chunks[i].size < best_chunk_size) {
                    best_chunk_id = i;
                    best_chunk_size = chunks[i].size;
                }
            }
        }
    }
#else
    for (size_t i = 0; i < chunks_num; ++i) {
        if (chunks[i].isFree && size <= chunks[i].size) {
            chunks[i].isFree = false;
            chunks[i].realUse = size;

            if (chunks[i].realUse < chunks[i].size) {
                if (chunks_num < CHUNKS_CAP) {
                    for (size_t k = chunks_num; k > i; --k) {
                        chunks[k] = chunks[k - 1];
                    }
                    chunks_num += 1;
                    chunks[i + 1].mem_ptr = (char*)(chunks[i + 1].mem_ptr) + chunks[i + 1].realUse;
                    chunks[i + 1].size = chunks[i].size - chunks[i].realUse;
                    chunks[i + 1].isFree = true;
                    chunks[i + 1].realUse = 0;
                    chunks[i].size = chunks[i].realUse;
                }
            }
            return chunks[i].mem_ptr;
        }
    }
#endif /* BEST_FIT */

#ifdef BEST_FIT
    if (best_chunk_id != -1) { //we have found the smallest chunk
        chunks[best_chunk_id].isFree = false;
        chunks[best_chunk_id].realUse = size;
        if (chunks[best_chunk_id].realUse < chunks[best_chunk_id].size) { //check for slicing
            if (chunks_num < CHUNKS_CAP) {
                for (size_t k = chunks_num; k > best_chunk_id; --k) {
                    chunks[k] = chunks[k - 1];
                }
                chunks_num += 1;
                chunks[best_chunk_id + 1].mem_ptr = (char*)chunks[best_chunk_id + 1].mem_ptr + chunks[best_chunk_id + 1].realUse;
                chunks[best_chunk_id + 1].size = chunks[best_chunk_id].size - chunks[best_chunk_id].realUse;
                chunks[best_chunk_id + 1].isFree = true;
                chunks[best_chunk_id + 1].realUse = 0;
                chunks[best_chunk_id].size = chunks[best_chunk_id].realUse;
            }
        }
        return chunks[best_chunk_id].mem_ptr;
    } else { //create and append a new chunk at the end
#endif /* BEST_FIT */
        chunks[chunks_num].mem_ptr = head_ptr;
        chunks[chunks_num].size = size;
        chunks[chunks_num].isFree = false;
        chunks[chunks_num].realUse = size;
        void *tmp = chunks[chunks_num].mem_ptr;
        ++chunks_num;
        allocated_size += size;
        head_ptr += size;
        return tmp;
#ifdef BEST_FIT
    }
#endif /* BEST_FIT */
}

void c_free(void *ptr)
{
    if (ptr == NULL || ptr < (void*)heap || ptr > (void*)head_ptr) {
        return;
    }

    for (int i = 0; i < chunks_num; ++i) {
        if (chunks[i].mem_ptr == ptr) {
            chunks[i].isFree = true;
            chunks[i].realUse = 0;
            return;
        }
    }
}

void dump_data()
{
    printf("allocated_size: %zu\n", allocated_size);
    printf("chunks_num: %zu\n", chunks_num);
    printf("head_ptr: %p\n", head_ptr);

    for (int i = 0; i < chunks_num; ++i) {
        putchar('|');
        printf("%zu|", chunks[i].size);
        printf("%zu|", chunks[i].realUse);
        for (int k = 0; k < chunks[i].size; ++k) {
            if (k < chunks[i].realUse) {
                putchar('*');
            } else {
                putchar('_');
            }
        }
        printf("|  ");
    }
        //printf("|mem_ptr: %p, size: %zu, realUse: %zu, %s|--", chunks[i].mem_ptr, chunks[i].size, chunks[i].realUse, chunks[i].isFree ? "true" : "false");
    putchar('\n');
}

#endif
