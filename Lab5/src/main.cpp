#include <iostream>
#include <memory_resource>
#include <string>

#include "memory_resource.h"
#include "queue.h"

struct BigStruct {
    int id;
    double value;
    std::string name;

    BigStruct() = default;
    BigStruct(int i, double v, std::string n) : id(i), value(v), name(std::move(n)) {}
};

int main() {
    const size_t BLOCK_SIZE = sizeof(BigStruct) > sizeof(int) ? sizeof(BigStruct) : sizeof(int);
    const size_t BLOCK_COUNT = 16;

    fixed_block_resource pool(BLOCK_SIZE, BLOCK_COUNT);

    std::cout << "Pool: total blocks = " << pool.total_blocks()
              << ", free = " << pool.free_count() << "\n";

    {
        Queue<int> q_int(8, &pool);
        std::cout << "\n-- Queue<int> demo --\n";
        for (int i = 1; i <= 5; ++i) {
            q_int.push(i * 10);
            std::cout << "pushed " << i*10 << ", free blocks = " << pool.free_count() << "\n";
        }

        std::cout << "Iterating over q_int: ";
        for (auto it = q_int.begin(); it != q_int.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n";

        while (!q_int.empty()) {
            std::cout << "front: " << q_int.front() << ", popping\n";
            q_int.pop();
            std::cout << "free blocks = " << pool.free_count() << ", allocated = " << pool.allocated_count() << "\n";
        }
    }

    {
        Queue<BigStruct> q_struct(6, &pool);
        std::cout << "\n-- Queue<BigStruct> demo --\n";
        q_struct.push(1, 3.14, "one");
        q_struct.push(2, 2.71, "two");
        q_struct.push(3, 1.41, "three");

        std::cout << "Iterating over q_struct:\n";
        for (auto it = q_struct.begin(); it != q_struct.end(); ++it) {
            std::cout << "  id=" << it->id << ", value=" << it->value << ", name=" << it->name << "\n";
        }

        std::cout << "Popping one element...\n";
        q_struct.pop();
        std::cout << "Now front: id=" << q_struct.front().id << "\n";

        q_struct.clear();
        std::cout << "After clear: free blocks = " << pool.free_count()
                  << ", allocated = " << pool.allocated_count() << "\n";
    }

    std::cout << "\nFinal pool status: free = " << pool.free_count()
              << ", allocated = " << pool.allocated_count() << "\n";

    return 0;
}
