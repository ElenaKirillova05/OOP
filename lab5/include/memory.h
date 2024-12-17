#pragma once
#include <memory_resource>
#include <vector>
#include <iostream>

class MemoryResource : public std::pmr::memory_resource {
private:
    std::vector<void*> allocated_blocks;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;

    void do_deallocate(void* ptr, size_t bytes, size_t alignment) override;

    bool do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

public:
    ~MemoryResource();
};

class TestMemoryResource : public MemoryResource {
public:
    using MemoryResource::do_allocate;
    using MemoryResource::do_deallocate;
};