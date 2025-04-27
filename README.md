# Simple Memory Allocator
Basic memory allocator written in C for learning purposes.
This toy library simulates simple dynamic memory management using a fixed-size heap buffer.

## Features
- Fixed-size heap initalization
- Manual memory allocation
- Manual memory freeing
- Basic block metadata tracking
- Alignment to 8-byte boundaries
- Block integrity checking using magic values
- Simple testing framework

## Usage
```c
// Initialize allocator with a buffer
allocator_init(heap, HEAP_SIZE);

// Allocate memory
void* block = alloc(64);

// Use memory
memset(block, 0xAA, 64);

// Print memory stats
allocator_dump();

// Free memory
free_alloc(block);

// Reset allocator
allocator_reset();
```
