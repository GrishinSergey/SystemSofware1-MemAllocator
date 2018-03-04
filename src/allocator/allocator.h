//
// Created by sergey on 10.10.17.
//

#ifndef CMEMALLOCATOR_ALLOCATOR_H
#define CMEMALLOCATOR_ALLOCATOR_H

#include <stddef.h>

void * mem_alloc(size_t size);

void * mem_realloc(void *address, size_t size);

void mem_free(void *address);

#endif //CMEMALLOCATOR_ALLOCATOR_H
