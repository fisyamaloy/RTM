#pragma once

#include <cstdlib>

class MemoryAllocationChecker
{
private:
    static size_t newCallAmount;
    static size_t delCallAmount;

public:
    void* operator new(size_t size)
    {
        void* p = malloc(size);
        /* It is not fully correct throwing an exception: if (p == nullptr) standart promise that
         'standart operator new' would call *new_handler* which would try (x times) allocating
         memory again */
        if (p == nullptr) throw std::bad_alloc();

        std::cout << "New call number " << ++newCallAmount << std::endl;
        return p;
    }

    void* operator new[](std::size_t size)
    {
        void* p = malloc(size);
        /* It is not fully correct throwing an exception: if (p == nullptr) standart promise that
         'standart operator new' would call *new_handler* which would try (x times) allocating
         memory again */
        if (p == nullptr) throw std::bad_alloc();

        std::cout << "New call number " << ++newCallAmount << std::endl;
        return p;
    }

    void operator delete(void* p)
    {
        free(p);
        std::cout << "Delete call number " << ++delCallAmount << std::endl;
    }

    void operator delete[](void* p, std::size_t)
    {
        free(p);
        std::cout << "Delete call number " << ++delCallAmount << std::endl;
    }
};