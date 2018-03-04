//
// Created by sergey on 10.10.17.
//

#include <stddef.h>
#include "memstruct.h"

size_t get_real_mem_size(size_t value)
{
    return ((value + 3) / 4) * 4;
}

void init_memory(size_t size)
{
    size = get_real_mem_size(size);
    memory_size = max_memory_size = (size <= 0) ? DEFAULT_MEMORY_SIZE : size;

    memory = (chunk *) malloc(memory_size);
    memory->id = 1;
    memory->status = FREE;
    memory->size = size;
    memory->next = NULL;

    last_added_chunk = 1;
}
