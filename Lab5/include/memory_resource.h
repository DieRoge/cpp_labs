#pragma once

#include <memory_resource>
#include <vector>
#include <mutex>
#include <cstdlib>
#include <new>
#include <iostream>
#include <algorithm>

class fixed_block_resource : public std::pmr::memory_resource {
public:
    fixed_block_resource(size_t block_size, size_t block_count);
    ~fixed_block_resource() noexcept override;

    size_t allocated_count() const;
    size_t free_count() const;
    size_t total_blocks() const;

protected:
    void* do_allocate(size_t bytes, size_t alignment) override;
    void  do_deallocate(void* p, size_t bytes, size_t alignment) override;
    bool  do_is_equal(const std::pmr::memory_resource& other) const noexcept override;

private:
    mutable std::mutex mut_;
    std::vector<void*> free_blocks_;
    std::vector<void*> allocated_blocks_;
    void* memory_pool_;
    size_t block_size_;
    size_t total_blocks_;
};
