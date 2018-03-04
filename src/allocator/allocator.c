//
// Created by sergey on 10.10.17.
//

#include <stddef.h>
#include <string.h>
#include "memstruct.h"


chunk * find_free_chunk(size_t necessary_size)
{
    size_t min_size = max_memory_size + 1;
    chunk * chunk_ptr = NULL;
    for (chunk * i = memory; i != NULL; i = i->next) {
        if ((!i->status) && (necessary_size <= i->size) && (min_size > i->size)) {
            chunk_ptr = i;
            min_size = i->size;
        }
    }
    return chunk_ptr;
}

chunk *get_new_mem_chunk(size_t fact_size)
{
    chunk *chunk_ptr = (chunk *) malloc(sizeof(chunk));
    chunk_ptr->size = fact_size;
    chunk_ptr->status = ALLOCATED;
    chunk_ptr->next = NULL;
    return chunk_ptr;
}

void * mem_alloc(size_t size)
{
    chunk * chunk_ptr = NULL, * free_chunk_ptr;
    size_t fact_size = get_real_mem_size(size);
    if (fact_size > 0 && fact_size <= memory_size) {
        free_chunk_ptr = find_free_chunk(fact_size);
        memory_size -= fact_size;
        if (free_chunk_ptr->size == fact_size) {
            free_chunk_ptr->status = ALLOCATED;
            chunk_ptr = free_chunk_ptr;
        } else {
            last_added_chunk++;
            free_chunk_ptr->size -= fact_size;
            chunk_ptr = get_new_mem_chunk(fact_size);
            chunk_ptr->next = free_chunk_ptr->next;
            free_chunk_ptr->next = chunk_ptr;
            chunk_ptr->id = last_added_chunk;
        }
    }
    return chunk_ptr;
}

chunk * find_chunk_by_address(int address)
{
    chunk * tmp_chunk_ptr = NULL;
    for (chunk * i = memory; i != NULL; i = i->next) {
        if (i->id == address) {
            tmp_chunk_ptr = i;
            break;
        }
    }
    return tmp_chunk_ptr;
}

chunk *find_prev_chunk(int address)
{
    chunk *prev = NULL;
    for (chunk * i = memory; i->next != NULL; i = i->next) {
        if (i->next->id == address) {
            prev = i;
            break;
        }
    }
    return prev;
}

void mem_free(void * addr)
{
    int address = *(int *) &addr;
    chunk * chunk_ptr = NULL, * next, * prev;
    if (address > 0) {
        chunk_ptr = find_chunk_by_address(address);
        if (chunk_ptr) {
            chunk_ptr->status = FREE;
            memory_size += chunk_ptr->size;
            prev = find_prev_chunk(address);
            next = prev->next->next;
            if (prev->status == FREE || next->status == FREE) {
                prev->next = next;
                prev->size += chunk_ptr->size;
                free(chunk_ptr);
            }
            if (prev->next->status == FREE) {
                prev->next = next;
                free(chunk_ptr);
                prev->size += chunk_ptr->size;
            }
        }
    }
}

void * mem_realloc(void * addr, size_t size)
{
    int address = *(int *) &addr;
    chunk * new_chunk_ptr = NULL, * old_chunk_ptr = NULL;
    size_t tmp_size = 0, fact_size = get_real_mem_size(size);
    if (addr == NULL) {
        new_chunk_ptr = mem_alloc(fact_size);
    } else if (fact_size == 0) {
        mem_free(addr);
    } else {
        old_chunk_ptr = find_chunk_by_address(address);
        if (old_chunk_ptr) {
            if (fact_size > old_chunk_ptr->size) {
                if (fact_size <= memory_size) {
                    mem_free(addr);
                    mem_alloc(fact_size);

                    for (chunk * i = memory; i != NULL; i = i->next) {
                        if (i->status == FREE) {
                            tmp_size += i->size;
                        }
                    }
                    memory_size = tmp_size;
                }
            } else if (old_chunk_ptr->size > fact_size) {
                find_free_chunk(0)->size += old_chunk_ptr->size - fact_size;
                old_chunk_ptr->size = fact_size;
            }
        }
    }
    return new_chunk_ptr;
}
