#pragma once

#include <cstddef>
#include <cstdint>

namespace engine::memory {

/// LIFO allocator for per-frame scratch memory.
/// Allocate forward, free by rewinding to a saved marker.
class StackAllocator {
public:
    using Marker = std::size_t;

    explicit StackAllocator(std::size_t capacityBytes);
    ~StackAllocator();

    StackAllocator(const StackAllocator&) = delete;
    StackAllocator& operator=(const StackAllocator&) = delete;

    void*  allocate(std::size_t size, std::size_t alignment = 4);
    Marker getMarker() const { return m_top; }
    void   freeToMarker(Marker marker);
    void   reset();

    [[nodiscard]] std::size_t capacity() const { return m_capacity; }
    [[nodiscard]] std::size_t used()     const { return m_top; }

private:
    std::size_t m_capacity;
    std::size_t m_top;
    uint8_t*    m_memory;
};

} // namespace engine::memory
