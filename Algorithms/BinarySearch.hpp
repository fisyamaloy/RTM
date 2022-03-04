#pragma once
#include <optional>
#include <vector>

template <class T>
[[nodiscard]] std::optional<size_t> binarySearch(const std::vector<T>& A, const T& elem)
{
    std::optional<size_t> opt_index_result;

    int left_index  = 0;
    int right_index = static_cast<int>(A.size()) - 1;
    while (left_index <= right_index)
    {
        int mid_index = (left_index + right_index) / 2;
        if (A[mid_index] < elem)
        {
            left_index = mid_index + 1;
        }
        else if (A[mid_index] > elem)
        {
            right_index = mid_index - 1;
        }
        else
        {
            opt_index_result = mid_index;
            break;
        }
    }

    return opt_index_result;
}
