#include "memory_resource.h"

fixed_block_resource::fixed_block_resource(size_t block_size, size_t block_count)
    : memory_pool_(nullptr)
    , block_size_(block_size)
    , total_blocks_(block_count)
{
    if (block_size_ == 0 || block_count == 0) {
        throw std::invalid_argument("block_size and block_count must be > 0");
    }

    memory_pool_ = std::malloc(block_size_ * block_count);
    if (!memory_pool_) {
        throw std::bad_alloc();
    }

    free_blocks_.reserve(block_count);
    allocated_blocks_.reserve(block_count);

    for (size_t i = 0; i < block_count; ++i) {
        void* block = static_cast<char*>(memory_pool_) + i * block_size_;
        free_blocks_.push_back(block);
    }
}

fixed_block_resource::~fixed_block_resource() noexcept {
    std::lock_guard<std::mutex> lk(mut_);

    if (!allocated_blocks_.empty()) {
        std::cerr << "Warning: " << allocated_blocks_.size() << " blocks still allocated at resource destruction\n";
    }

    if (memory_pool_) {
        std::free(memory_pool_);
        memory_pool_ = nullptr;
    }
}

size_t fixed_block_resource::allocated_count() const {
    std::lock_guard<std::mutex> lk(mut_);
    return allocated_blocks_.size();
}

size_t fixed_block_resource::free_count() const {
    std::lock_guard<std::mutex> lk(mut_);
    return free_blocks_.size();
}

size_t fixed_block_resource::total_blocks() const {
    return total_blocks_;
}

void* fixed_block_resource::do_allocate(size_t bytes, size_t alignment) {
    std::lock_guard<std::mutex> lk(mut_);

    if (bytes > block_size_) {
        throw std::bad_alloc();
    }

    if (free_blocks_.empty()) {
        throw std::bad_alloc();
    }

    void* block = free_blocks_.back();
    free_blocks_.pop_back();
    allocated_blocks_.push_back(block);

    uintptr_t addr = reinterpret_cast<uintptr_t>(block);
    if (alignment != 0 && (addr % alignment) != 0) {
        std::cerr << "Warning: allocated block does not satisfy alignment requirement\n";
    }

    return block;
}

void fixed_block_resource::do_deallocate(void* p, size_t bytes, size_t /*alignment*/) {
    if (p == nullptr) return;

    std::lock_guard<std::mutex> lk(mut_);

    auto it = std::find(allocated_blocks_.begin(), allocated_blocks_.end(), p);
    if (it == allocated_blocks_.end()) {
        std::cerr << "Warning: deallocating unknown pointer\n";
        return;
    }

    allocated_blocks_.erase(it);
    free_blocks_.push_back(p);
}

bool fixed_block_resource::do_is_equal(const std::pmr::memory_resource& other) const noexcept {
    return this == &other;
}
