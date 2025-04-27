//
// Created by Willam Galvin on 2025-04-27.
//

#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>
#include <string.h>
#include "allocator.h"

#define HEAP_SIZE 1024

char heap[HEAP_SIZE];

int run_tests() {
    printf("Initializing allocator...\n\n");
    allocator_init(heap, HEAP_SIZE);
    allocator_dump();
    printf("\n");

    const size_t test_block_sizes[] = {64, 128};
    const size_t num_blocks = sizeof(test_block_sizes) / sizeof(test_block_sizes[0]);
    void* allocated_blocks[num_blocks];

    for (size_t i = 0; i < num_blocks; i++) {
        size_t block_size = test_block_sizes[i];
        printf("Allocating block %zu (%zu bytes)...\n", i, block_size);

        void* b = alloc(block_size);
        allocated_blocks[i] = b;

        if (b == NULL) {
            printf("Failed to allocate block %zu.\n", i);
            return 0;
        }

        memset(b, 0xAA, block_size);
    }

    printf("\nAllocator state after test allocations:\n");
    allocator_dump();
    printf("\n");

    for (size_t i = 0; i < num_blocks; i++) {
        printf("Freeing block %zu...\n", i);

        free_alloc(allocated_blocks[i]);
    }

    printf("\nAllocator state after freeing all blocks:\n");
    allocator_dump();
    printf("\n");

    return 1;
}

#endif //TESTS_H
