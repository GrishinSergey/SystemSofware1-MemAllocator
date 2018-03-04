#include <stdio.h>
#include "allocator/memstruct.h"
#include "allocator/allocator.h"
#include "printer.h"

int main() {
    init_memory(1024);

    void * p1 = mem_alloc(100);
    void * p2 = mem_alloc(200);
    void * p3 = mem_alloc(300);
    void * p4 = mem_alloc(400);
//    void * p5 = mem_alloc(24);

    print();

    mem_free((void *) 5);

    printf("\n\n");
    print();

    mem_realloc((void *) 4, 120);

    printf("\n\n");
    print();

    mem_realloc((void *) 4, 320);

    printf("\n\n");
    print();

    printf("\n\n");

    return 0;
}