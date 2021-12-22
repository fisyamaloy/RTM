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
    Vector(const Vector<T>& vector) noexcept;
    ~Vector() noexcept { delete[] A; }

    Vector(const std::initializer_list<T>& list) noexcept;

    inline T& at(const size_t index) const;
    inline T& operator[](const int index) const noexcept { return A[index]; }

    inline const size_t size() const noexcept { return mSize; }
    inline const size_t capacity() const noexcept { return mCapacity; }

    void push_back(const T& element);
    void push_front(const T& elem);
};

// Definiton

template <class T>
void Vector<T>::alloc_new()
{
    mCapacity *= 2;
    T* newArray = new T[mCapacity];
    for (auto i = 0; i < mSize; ++i)
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

    for (auto i = 0; i < vector.mSize; ++i)
    {
        A[i] = vector.A[i];
    }

    return *this;
}

template <class T>
Vector<T>::Vector(const std::initializer_list<T>& list) noexcept
{
    mSize     = list.size();
    mCapacity = list.size() * 2;
    A         = new T[mCapacity];

    size_t i  = 0;
    for (const auto& elem : list)
    {
        A[i++] = elem;
    }
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
void Vector<T>::push_back(const T& element)
{
    if (mSize + 1 > mCapacity)
    {
        alloc_new();
    }

    A[mSize++] = element;
}

template <class T>
void Vector<T>::push_front(const T& elem)
{
    if (mSize + 1 > mCapacity)
    {
        alloc_new();
    }

    T* newArray = new T[++mSize];
    newArray[0] = elem;
    for (auto i = 1; i < mSize; ++i)
    {
        newArray[i] = A[i - 1];
    }

    delete[] A;
    A = newArray;
}
}  // namespace Danils
