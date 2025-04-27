//
// Created by Willam Galvin on 2025-04-26.
//

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

const size_t block_size = 8;

typedef struct BlockHeader {
    uint32_t magic;
    size_t size;
    int is_free;
    struct BlockHeader* next;
} BlockHeader;

void* heap_start = NULL;
void* heap_end = NULL;
void* heap_ptr = NULL;
BlockHeader* prev_block = NULL;

uintptr_t align_up(uintptr_t addr) {
    const uintptr_t misalignment = addr % block_size;

    if (misalignment == 0) {
        return addr;
    }

    return addr + (block_size - misalignment);
}

void allocator_init(void* buffer, size_t size) {
    heap_start = buffer;
    heap_ptr = buffer;
    heap_end = (char*)buffer + size;
}

void* alloc(size_t size) {
    const uintptr_t current_addr = align_up((uintptr_t)heap_ptr);
    BlockHeader* block = (BlockHeader*)current_addr;

    void* user_mem = block + 1;
    uintptr_t new_end = (uintptr_t)user_mem + size;

    if ((void*)new_end <= heap_end) {
        block->magic = 0xDEADBEEF;
        block->size = size;
        block->is_free = 0;
        block->next = NULL;

        if (prev_block != NULL) {
            prev_block->next = block;
        }

        prev_block = block;
        heap_ptr = (void*)new_end;

        return user_mem;
    }

    return NULL;
}

int free_alloc(void* addr) {
    if (addr == NULL) {
        return 0;
    }

    if (
        !((char*)addr >= heap_start && (char*)addr < heap_ptr) ||
        (uintptr_t)addr % block_size != 0
    ) {
        return 0;
    }

    BlockHeader* block = (BlockHeader*)addr - 1;

    if (block->magic != 0xDEADBEEF) {
        return 0;
    }

    block->is_free = 1;
    block->magic = 0x0;

    return 1;
}

int is_free(void* addr) {
    if (addr == NULL) {
        return 0;
    }

    if (
        !((char*)addr >= heap_start && (char*)addr < heap_ptr) ||
        (uintptr_t)addr % block_size != 0
        ) {
        return 0;
    }

    BlockHeader* block = (BlockHeader*)addr - 1;

    if (
        block->magic != 0xDEADBEEF &&
        block->magic != 0x0
        ) {
        return 0;
    }

    return block->is_free;
}

void allocator_reset() {
    heap_ptr = heap_start;
    prev_block = NULL;
}

size_t allocator_used() {
    return (uintptr_t)heap_ptr - (uintptr_t)heap_start;
}

size_t allocator_free() {
    return (uintptr_t)heap_end - (uintptr_t)heap_ptr;
}

void allocator_dump() {
    printf("=== Allocator State ===\n");
    printf("Heap start:    %p\n", heap_start);
    printf("Heap pointer:  %p\n", heap_ptr);
    printf("Heap end:      %p\n", heap_end);
    printf("Bytes used:    %zu\n", allocator_used());
    printf("Bytes free:    %zu\n", allocator_free());
}

#endif //ALLOCATOR_H