#include "stack_allocator.h"

namespace engine::memory {

StackAllocator::StackAllocator(std::size_t capacityBytes)
    : m_capacity{capacityBytes}
    , m_top{0}
    , m_memory{nullptr}
{
    // TODO: allocate backing buffer
}

StackAllocator::~StackAllocator() {
    // TODO: free backing buffer
}

void* StackAllocator::allocate(std::size_t size, std::size_t alignment) {
    // TODO: bump m_top with alignment, return pointer, or nullptr if full
    return nullptr;
}

void StackAllocator::freeToMarker(Marker marker) {
    // TODO: rewind m_top to marker
}

void StackAllocator::reset() {
    // TODO: set m_top back to 0
}

} // namespace engine::memory
