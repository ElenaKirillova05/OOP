#include "../include/memory.h"
#include <algorithm>

void* MemoryResource::do_allocate(size_t bytes, size_t alignment) {
    void* ptr = ::operator new(bytes, std::align_val_t(alignment));
    allocated_blocks.push_back(ptr);
    #ifndef NDEBUG
    std::cout << "Allocated " << bytes << " bytes at " << ptr << std::endl;
    #endif
    return ptr;
}

void MemoryResource::do_deallocate(void* ptr, size_t bytes, size_t alignment) {
    (void)bytes;
    (void)alignment;

    auto it = std::find(allocated_blocks.begin(), allocated_blocks.end(), ptr);
    if (it != allocated_blocks.end()) {
        allocated_blocks.erase(it);
        #ifndef NDEBUG
        std::cout << "Deallocated memory at " << ptr << std::endl;
#endif
        ::operator delete(ptr, std::align_val_t(alignment));
    } else {
        std::cerr << "Attempted to deallocate unknown pointer: " << ptr << std::endl;
    }
}

bool MemoryResource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}

MemoryResource::~MemoryResource() {
    for (void* ptr : allocated_blocks) {
#ifndef NDEBUG
        std::cout << "Cleaning memory at " << ptr << std::endl;
#endif
        ::operator delete(ptr);
    }
    allocated_blocks.clear();
}