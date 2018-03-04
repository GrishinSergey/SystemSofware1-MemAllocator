//
// Created by sergey on 10.10.17.
//

#ifndef CMEMALLOCATOR_MEMCHUNK_H
#define CMEMALLOCATOR_MEMCHUNK_H


#include <malloc.h>

static const size_t DEFAULT_MEMORY_SIZE = 2048;

typedef enum { FREE, ALLOCATED } STATUS;

typedef struct tag_mem_chunk {
    int id;
    size_t size;
    STATUS status;
    struct tag_mem_chunk *next;
} chunk;

chunk * memory;

size_t memory_size, max_memory_size;

int last_added_chunk;


void init_memory(size_t size);

size_t get_real_mem_size(size_t value);


#endif //CMEMALLOCATOR_MEMCHUNK_H
