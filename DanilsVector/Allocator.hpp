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
        return static_cast<T*>(::operator new(n * sizeof(T)));  // Function operator new
    }

    void deallocate(T* p, size_t)
    {
        ::operator delete(p);  // Function operator delete
    }

    template <class... Args>
    void construct(T* ptr, Args&&... args)
    {
        new (ptr) T(std::forward<Args>(args)...); // Placement new
    }

    void destroy(T* ptr) { ptr->~T(); }
};
}  // namespace Danils
