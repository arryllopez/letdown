#pragma once

#include <cstddef>
#include <cstdint>

namespace engine::memory {

/// Fixed-size block allocator — perfect for entities, particles, etc.
/// Operates on a pre-allocated slab so we never hit the system allocator at runtime.
class PoolAllocator {
public:
    PoolAllocator(std::size_t blockSize, std::size_t blockCount);
    ~PoolAllocator();

    PoolAllocator(const PoolAllocator&) = delete;
    PoolAllocator& operator=(const PoolAllocator&) = delete;

    void* allocate();
    void  deallocate(void* ptr);
    void  reset();

    [[nodiscard]] std::size_t blockSize()   const { return m_blockSize; }
    [[nodiscard]] std::size_t blockCount()  const { return m_blockCount; }
    [[nodiscard]] std::size_t freeCount()   const { return m_freeCount; }

private:
    struct FreeNode { FreeNode* next; };

    std::size_t  m_blockSize;
    std::size_t  m_blockCount;
    std::size_t  m_freeCount;
    uint8_t*     m_memory;
    FreeNode*    m_freeList;
};

} // namespace engine::memory
