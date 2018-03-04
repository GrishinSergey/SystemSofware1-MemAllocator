cmake_minimum_required(VERSION 3.8)
project(CMemAllocator)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/main.c

        src/allocator/allocator.h
        src/allocator/allocator.c

        src/allocator/memstruct.h
        src/allocator/memstruct.c

        src/printer.c
        src/printer.h
)
add_executable(CMemAllocator ${SOURCE_FILES})