#pragma once
#include <cstdlib>

#include "VectorException.hpp"

namespace Danils
{
template <class T>
class Vector
{
private:
    T*     A;
    size_t mSize;
    size_t mCapacity;

    void alloc_new();

public:
    Vector() noexcept;
    Vector(const size_t length);
    Vector(const std::initializer_list<T>& list) noexcept;
    Vector(const Vector<T>& vector) noexcept;

    ~Vector() noexcept { delete[] A; }

    inline T& at(const int index) const;
    inline T& at(const size_t index) const;
    inline T& operator[](const int index) const noexcept { return A[index]; }
    inline T& operator[](const size_t index) const noexcept { return A[index]; }

    inline constexpr size_t size() const noexcept { return mSize; }
    inline constexpr size_t capacity() const noexcept { return mCapacity; }

    void reserve(const size_t newCapacity) noexcept;

    void insert(const int index, const T& elem);
    void erase(const int index);

    void push_back(const T& elem) { insert(static_cast<int>(mSize), elem); }
    void push_front(const T& elem) { insert(0, elem); }
    void pop_back(const T& elem) { erase(mSize - 1); }
    void pop_front(const T& elem) { erase(0); }
};

// Definiton

template <class T>
void Vector<T>::alloc_new()
{
    T* newArray = new T[mCapacity];
    for (size_t i = 0; i < mSize; ++i)
    {
        newArray[i] = A[i];
    }

    delete[] A;
    A = newArray;
}

template <class T>
Vector<T>::Vector() noexcept
{
    mCapacity = 20;
    A         = new T[mCapacity];
    mSize     = 0;
}

template <class T>
Vector<T>::Vector(const Vector<T>& vector) noexcept
{
    mSize     = vector.size();
    mCapacity = vector.capacity();
    A         = new T[mCapacity];

    for (size_t i = 0; i < vector.mSize; ++i)
    {
        A[i] = vector.A[i];
    }
}

template <class T>
Vector<T>::Vector(const size_t length)
{
    A         = new T[length];
    mSize     = length;
    mCapacity = length * 2;
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T>& list) noexcept
{
    mSize     = list.size();
    mCapacity = list.size() * 2;
    A         = new T[mCapacity];

    size_t i = 0;
    for (const auto& elem : list)
    {
        A[i++] = elem;
    }
}

template <class T>
T& Vector<T>::at(const int index) const
{
    if (index < mSize)
    {
        return A[index];
    }

    throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
}

template <class T>
T& Vector<T>::at(const size_t index) const
{
    if (index < mSize)
    {
        return A[index];
    }

    throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
}

template <class T>
void Vector<T>::reserve(const size_t newCapacity) noexcept
{
    if (newCapacity <= mCapacity)
    {
        return;
    }

    mCapacity = newCapacity;
    alloc_new();
}

template <class T>
void Vector<T>::insert(const int index, const T& elem)
{
    if (mSize >= mCapacity)
    {
        mCapacity = mSize * 2;
        alloc_new();
    }

    for (int i = static_cast<int>(mSize) - 1; i >= index; --i)
    {
        A[i + 1] = A[i];
    }
    A[index] = elem;
    mSize++;
}

template <class T>
void Vector<T>::erase(const int index)
{
    if (index < 0 || index >= static_cast<int>(mSize))
    {
        throw VectorException(VectorException::ErrorsCodes::OUT_OF_RANGE);
    }

    for (size_t i = index; i < mSize - 1; ++i)
    {
        A[i] = A[i + 1];
    }
    A[mSize - 1] = T();

    mSize--;
}
}  // namespace Danils
