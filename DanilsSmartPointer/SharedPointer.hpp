#include <mutex>

namespace Danils
{
    template <class T>
    class SharedPointer
    {
        T*      ptr     = nullptr;
        size_t* counter = nullptr;
        mutable std::mutex mutex;

    public:
        SharedPointer() = default;
        SharedPointer(T* ptr) : ptr(ptr), counter(new size_t(1)) {}
        SharedPointer(const SharedPointer<T>& other) : ptr(other.ptr), counter(other.counter)
        {
            ++*counter;
        }
        SharedPointer(SharedPointer<T>&& other) noexcept : ptr(other.ptr), counter(other.counter)
        {
            other.ptr     = nullptr;
            other.counter = nullptr;
        }
        ~SharedPointer() noexcept
        {
            std::lock_guard<std::mutex> lg(mutex);

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

        constexpr size_t use_count() const 
        {
            return *counter;
        }
    };

}  // namespace Danils
