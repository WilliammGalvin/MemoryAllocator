cmake_minimum_required(VERSION 3.28)
project(MemoryAllocator C)

set(CMAKE_C_STANDARD 23)

add_executable(MemoryAllocator main.c
        allocator.h
        tests.h
)
