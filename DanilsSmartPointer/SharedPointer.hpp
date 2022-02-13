#pragma once
#include <mutex>
#include <utility>

namespace Danils
{
    template <class T>
    class SharedPointer
    {
        T*                  ptr     = nullptr;
        size_t*             counter = nullptr;
        mutable std::mutex* mutex   = nullptr;

        template <class U, class... Args>
        friend SharedPointer<U> make_shared(Args&&... args);

    public:
        SharedPointer() = default;
        SharedPointer(T* ptr) : ptr(ptr), counter(new size_t(1)), mutex(new std::mutex) {}
        SharedPointer(const SharedPointer<T>& other)
            : ptr(other.ptr), counter(other.counter), mutex(other.mutex)
        {
            ++*counter;
        }
        SharedPointer(SharedPointer<T>&& other) noexcept
            : ptr(other.ptr), counter(other.counter), mutex(other.mutex)
        {
            other.ptr     = nullptr;
            other.counter = nullptr;
            other.mutex   = nullptr;
        }
        ~SharedPointer() noexcept
        {
            std::lock_guard<std::mutex> lg(*mutex);

            if (*counter != 1)
            {
                --*counter;
                return;
            }

            delete ptr;
            delete counter;
        }

        T& operator*() const { return *ptr; }
        T* operator->() const { return ptr; }

        constexpr size_t use_count() const { return *counter; }
    };

    template <class U, class... Args>
    SharedPointer<U> make_shared(Args&&... args)
    {
        auto ptr = new U(std::forward<Args>(args)...);
        return SharedPointer<U>(ptr);
    }

}  // namespace Danils
