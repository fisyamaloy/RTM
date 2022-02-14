#pragma once
#include <cstdlib>

#include "Allocator.hpp"
#include "VectorException.hpp"

namespace Danils
{
template <class T, class Alloc = Danils::Allocator<T>>
class Vector
{
private:
    const size_t CAPACITY_ENCREASE_FACTOR = 2;
    size_t       mSize;
    size_t       mCapacity;
    T*           A;
    Alloc        mAlloc;

    using AllocTraits = std::allocator_traits<Alloc>;

    void alloc_new();

public:
    Vector() noexcept : mSize(0), mCapacity(0), A(nullptr){};
    Vector(const size_t length, const T& elem = T()) noexcept;
    Vector(const size_t length, T&& elem) noexcept;
    Vector(const std::initializer_list<T>& list) noexcept;
    Vector(std::initializer_list<T>&& list) noexcept;
    Vector(const Vector<T>& vector);
    Vector(Vector<T>&& vector) noexcept;
    ~Vector() noexcept;

    inline T& at(const int index) const;
    inline T& at(const size_t index) const;
    inline T& operator[](const int index) const noexcept { return A[index]; }
    inline T& operator[](const size_t index) const noexcept { return A[index]; }

    inline constexpr size_t size() const noexcept { return mSize; }
    inline constexpr size_t capacity() const noexcept { return mCapacity; }

    void reserve(const size_t newCapacity) noexcept;

    void insert(const int index, const T& elem);
    void insert(const int index, T&& elem);
    void erase(const int index);

    void push_back(const T& elem) { insert(static_cast<int>(mSize), elem); }
    void push_back(T&& elem) { insert(static_cast<int>(mSize), std::move(elem)); }
    void push_front(const T& elem) { insert(0, elem); }
    void push_front(T&& elem) { insert(0, std::move(elem)); }
    void pop_back() { erase(static_cast<int>(mSize) - 1); }
    void pop_front() { erase(0); }
};

// Definiton

template <class T, class Alloc>
void Vector<T, Alloc>::alloc_new()
{
    T*     newArray = AllocTraits::allocate(mAlloc, mCapacity);
    size_t i        = 0;
    try
    {
        for (; i < mSize; ++i)
        {
            AllocTraits::construct(mAlloc, newArray + i, A[i]);
        }
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
        {
            AllocTraits::destroy(mAlloc, newArray + j);
        }
        AllocTraits::deallocate(mAlloc, newArray, mCapacity);
        throw;
    }

    for (i = 0; i < mSize; ++i)
    {
        AllocTraits::destroy(mAlloc, A + i);
    }
    AllocTraits::deallocate(mAlloc, A, mCapacity);

    A = newArray;
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const Vector<T>& vector)
{
    mSize     = vector.mSize;
    mCapacity = vector.mCapacity;
    A         = AllocTraits::allocate(mAlloc, mCapacity);

    size_t i = 0;
    try
    {
        for (; i < vector.mSize; ++i)
        {
            AllocTraits::construct(mAlloc, A + i, vector[i]);
        }
    }
    catch (...)
    {
        for (size_t j = 0; j < i; ++j)
        {
            AllocTraits::destroy(mAlloc, A + j);
        }
        AllocTraits::deallocate(mAlloc, A, mCapacity);
        throw;
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(Vector<T>&& vector) noexcept
{
    A                = vector.A;
    mCapacity        = vector.mCapacity;
    mSize            = vector.mSize;
    vector.A         = nullptr;
    vector.mCapacity = 0;
    vector.mSize     = 0;
}

template <class T, class Alloc>
Vector<T, Alloc>::~Vector() noexcept
{
    for (size_t i = 0; i < mSize; ++i)
    {
        AllocTraits::destroy(mAlloc, A + i);
    }
    AllocTraits::deallocate(mAlloc, A, mCapacity);
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const size_t length, const T& elem) noexcept
{
    mSize     = length;
    mCapacity = length * CAPACITY_ENCREASE_FACTOR;
    A         = AllocTraits::allocate(mAlloc, mCapacity);
    for (size_t i = 0; i < mSize; ++i)
    {
        AllocTraits::construct(mAlloc, A + i, elem);
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const size_t length, T&& elem) noexcept
{
    mSize     = length;
    mCapacity = length * CAPACITY_ENCREASE_FACTOR;
    A         = AllocTraits::allocate(mAlloc, mCapacity);
    for (size_t i = 0; i < mSize; ++i)
    {
        AllocTraits::construct(mAlloc, A + i, std::move(elem));
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(const std::initializer_list<T>& list) noexcept
{
    mSize     = list.size();
    mCapacity = list.size() * CAPACITY_ENCREASE_FACTOR;
    A         = AllocTraits::allocate(mAlloc, mCapacity);

    size_t i = 0;
    for (const auto& elem : list)
    {
        AllocTraits::construct(mAlloc, A + i, elem);
        ++i;
    }
}

template <class T, class Alloc>
Vector<T, Alloc>::Vector(std::initializer_list<T>&& list) noexcept
{
    mSize     = list.size();
    mCapacity = list.size() * CAPACITY_ENCREASE_FACTOR;
    A         = AllocTraits::allocate(mAlloc, mCapacity);

    size_t i = 0;
    for (auto&& elem : list)
    {
        AllocTraits::construct(mAlloc, A + i, std::move(elem));
        ++i;
    }
}

template <class T, class Alloc>
T& Vector<T, Alloc>::at(const int index) const
{
    if (index >= 0 && index < static_cast<int>(mSize))
    {
        return A[index];
    }

    throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
}

template <class T, class Alloc>
T& Vector<T, Alloc>::at(const size_t index) const
{
    if (index >= 0 && index < mSize)
    {
        return A[index];
    }

    throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
}

template <class T, class Alloc>
void Vector<T, Alloc>::reserve(const size_t newCapacity) noexcept
{
    if (newCapacity <= mCapacity)
    {
        return;
    }

    mCapacity = newCapacity;
    alloc_new();
}

template <class T, class Alloc>
void Vector<T, Alloc>::insert(const int index, const T& elem)
{
    if (index < 0)
    {
        throw Danils::VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
    }

    if (mSize >= mCapacity)
    {
        mCapacity *= CAPACITY_ENCREASE_FACTOR;
        alloc_new();
    }

    for (int i = static_cast<int>(mSize) - 1; i >= index; --i)
    {
        AllocTraits::construct(mAlloc, A + i + 1, A[i]);
    }
    AllocTraits::construct(mAlloc, A + index, elem);

    mSize++;
}

template <class T, class Alloc>
void Vector<T, Alloc>::insert(const int index, T&& elem)
{
    if (index < 0)
    {
        throw Danils::VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
    }

    if (mSize >= mCapacity)
    {
        mCapacity *= CAPACITY_ENCREASE_FACTOR;
        alloc_new();
    }

    for (int i = static_cast<int>(mSize) - 1; i >= index; --i)
    {
        AllocTraits::construct(mAlloc, A + i + 1, std::move(A[i]));
    }
    AllocTraits::construct(mAlloc, A + index, std::move(elem));

    mSize++;
}

template <class T, class Alloc>
void Vector<T, Alloc>::erase(const int index)
{
    if (index < 0 || index >= static_cast<int>(mSize))
    {
        throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
    }

    for (size_t i = index; i < mSize - 1; ++i)
    {
        AllocTraits::construct(mAlloc, A + i, A[i + 1]);
    }
    AllocTraits::construct(mAlloc, A + mSize - 1, T());

    mSize--;
}
}  // namespace Danils
