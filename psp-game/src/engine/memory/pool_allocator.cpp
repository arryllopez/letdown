#include "pool_allocator.h"

namespace engine::memory {

PoolAllocator::PoolAllocator(std::size_t blockSize, std::size_t blockCount)
    : m_blockSize{blockSize}
    , m_blockCount{blockCount}
    , m_freeCount{0}
    , m_memory{nullptr}
    , m_freeList{nullptr}
{
    // TODO: allocate slab (m_blockSize * m_blockCount), build free list
}

PoolAllocator::~PoolAllocator() {
    // TODO: release slab
}

void* PoolAllocator::allocate() {
    // TODO: pop head of free list, return pointer
    return nullptr;
}

void PoolAllocator::deallocate(void* ptr) {
    // TODO: push block back onto free list
}

void PoolAllocator::reset() {
    // TODO: rebuild entire free list from slab
}

} // namespace engine::memory
