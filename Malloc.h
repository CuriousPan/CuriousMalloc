#ifndef MALLOC_H
#define MALLOC_H

#include <stddef.h>
#include <stdbool.h>

#define HEAP_SIZE 640000
#define CHUNKS_CAP 1024

typedef char byte;

typedef struct {
    void *mem_ptr;
    size_t size;
    bool isFree;
    size_t realUse;
} Chunk;

byte heap[HEAP_SIZE];

Chunk chunks[CHUNKS_CAP];

void *c_malloc(size_t size);

void c_free(void *ptr);

void dump_data();

#endif
