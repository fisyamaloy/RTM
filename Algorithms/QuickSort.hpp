#include <vector>

namespace Algorithm
{
    template <class T>
    void quick_sort(std::vector<T>& A, const int left_index, const int right_index)
    {
        if (left_index >= right_index)
        {
            return;
        }

        int     left     = left_index;
        int     right    = right_index;
        const T mid_elem = A[(left_index + right_index) / 2];

        while (left <= right)
        {
            while (A[left] < mid_elem)
            {
                ++left;
            }
            while (A[right] > mid_elem)
            {
                --right;
            }

            if (left <= right)
            {
                std::swap(A[left], A[right]);
                ++left;
                --right;
            }
        }

        quick_sort(A, left_index, right);
        quick_sort(A, left, right_index);
    }

}  // namespace Algorithm.
