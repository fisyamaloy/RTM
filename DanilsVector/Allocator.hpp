#pragma once
#include <cstdlib>

namespace Danils
{
// Base allocator
template <class T>
struct Allocator
{
    T* allocate(const size_t n)
    {
        return ::operator new(n * sizeof(T));  // Function operator new
    }

    void deallocate(T* p, size_t)
    {
        ::operator delete(p);  // Function operator delete
    }

    // TODO: move semantics for args is needed
    template <class... Args>
    void construct(T* ptr, const Args&... args)
    {
        new (ptr) T(args...);
    }

    void destroy(T* ptr) { ptr->~T(); }
};
}  // namespace Danils
