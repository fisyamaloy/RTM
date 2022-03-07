#include <algorithm>
#include <iostream>
#include <vector>

#include "BinarySearch.hpp"
#include "QuickSort.hpp"

int main()
{
    std::vector<int> A = {15, -10, 1, 3, -5, -3, 0, 20};

    Algorithm::quick_sort(A, 0, static_cast<int>(A.size()) - 1);
    auto optIndex = Algorithm::binarySearch(A, 1);
    if (optIndex.has_value())
    {
        std::cout << *optIndex << std::endl;
    }
    else
    {
        std::cout << "The same element was not founded" << std::endl;
    }

    return 0;
}
