#pragma once

#include "pool_allocator.h"
#include "stack_allocator.h"

namespace engine::memory {

/// Top-level owner of all allocators.
/// Call init() once at startup; everything else grabs sub-allocators from here.
struct MemoryManager {
    PoolAllocator  entityPool;   // fixed blocks for game entities
    StackAllocator frameStack;   // per-frame scratch (reset every tick)

    MemoryManager()
        : entityPool(128, 256)   // 128-byte blocks x 256
        , frameStack(64 * 1024)  // 64 KB scratch
    {}

    // TODO: add helpers — typed allocate<T>(), stats dump, etc.
};

} // namespace engine::memory
