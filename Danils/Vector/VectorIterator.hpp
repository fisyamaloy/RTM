#pragma once
#include <cstddef>
#include <cstdio>

namespace Danils
{
    template <class T, bool isConst>
    class VectorIterator
    {
        friend class VectorIterator<T, !isConst>;

        using value_pointer = std::conditional_t<isConst, const T*, T*>;
        value_pointer ptr_;

    public:
        explicit VectorIterator(value_pointer p) : ptr_(p) {}

        // Member typedefs required by std::iterator_traits
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = std::conditional_t<isConst, const T*, T*>;
        using reference         = std::conditional_t<isConst, const T&, T&>;
        using iterator_category = std::random_access_iterator_tag;

        reference operator*() const { return *ptr_; }
        auto&     operator++()
        {
            ++ptr_;
            return *this;
        }
        auto operator++(int)
        {
            auto result = *this;
            ++*this;
            return result;
        }

        // Support comparison between iterator and const_iterator types
        template <bool R>
        bool operator==(const VectorIterator<value_type, R>& rhs) const
        {
            return *ptr_ == *rhs.ptr_;
        }

        template <bool R>
        bool operator!=(const VectorIterator<value_type, R>& rhs) const
        {
            return *ptr_ != *rhs.ptr_;
        }

        // Support implicit conversion of iterator to const_iterator (but not vice versa)
        operator VectorIterator<value_type, true>() const
        {
            return VectorIterator<value_type, true>{ptr_};
        }
    };

}  // namespace Danils
