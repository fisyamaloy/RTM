#pragma once
#include <cstdlib>
//#define DEBUG

namespace Danils
{
// Base allocator
template <class T>
struct Allocator
{
    using pointer            = T*;
    using const_pointer      = T const*;
    using void_pointer       = void*;
    using const_void_pointer = void const*;
    using size_type          = size_t;
    using difference_type    = ptrdiff_t;
    using value_type         = T;

    pointer allocate(const size_type n)
    {
        size_type size = n * sizeof(value_type);

#ifdef DEBUG
        std::cout << "Allocated " << size << " bytes" << std::endl;
#endif  // DEBUG

        return static_cast<pointer>(::operator new(size));  // Function operator new
    }

    void deallocate(pointer p, [[maybe_unused]] size_type size)
    {
#ifdef DEBUG
        std::cout << "Deallocated " << size * sizeof(value_type) << " bytes" << std::endl;
#endif  // DEBUG

        ::operator delete(p);  // Function operator delete
    }

    template <class... Args>
    void construct(pointer ptr, Args&&... args)
    {
        new (ptr) T(std::forward<Args>(args)...);  // Placement new
    }

    void destroy(pointer ptr) { ptr->~T(); }
};
}  // namespace Danils
