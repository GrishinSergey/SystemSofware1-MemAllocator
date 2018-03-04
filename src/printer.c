//
// Created by sergey on 07.11.17.
//

#include "printer.h"
#include "allocator/memstruct.h"


void print()
{
    for (chunk * i = memory; i != NULL; i = i->next) {
        printf("blockID: %d\n", i->id);
        printf("         size: %d\n", (int) i->size);
        if (i->status == ALLOCATED) {
            printf("         status: allocated\n");
        } else {
            printf("         status: free\n");
        }
    }
    printf("allocated memory size: %d\n", max_memory_size - memory_size);
    printf("free memory size:      %d\n", memory_size);
    printf("all memory size:       %d\n", max_memory_size);
}
