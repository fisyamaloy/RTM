#pragma once
#include <cstdlib>

namespace Danils
{
//DANGER! Never use this var from namespace
namespace
{
size_t usedMemory = 0;
}

struct MemoryAllocationChecker
{
public:
    static void* operator new(size_t size)
    {
        usedMemory += size;
        return malloc(size);
    }

    static void operator delete(void* p, size_t size)
    {
        free(p);
        usedMemory -= size;
    }
    void* operator new[](std::size_t size) 
    {
        usedMemory += size;
        return malloc(size);
    }
    void operator delete[](void* p, std::size_t size) 
    {
        free(p);
        usedMemory -= size;
    }
};
}  // namespace Danils
