#pragma once
#include <iostream>
#include <numeric>
#include <optional>
#include <vector>

/*
std::optional is an class which can store some value it is unnecessary: /
it can store nothing - std::nullopt.
*/
namespace optional_examples
{
    const std::optional<int> findFirstNegativeNumber(const int A[], const size_t size)
    {
        for (size_t i = 0; i < size; ++i)
        {
            if (A[i] < 0)
            {
                return std::make_optional(A[i]);
            }
        }

        return std::nullopt;
    }

    void example_1()
    {
        std::cout << "example_1:" << std::endl;

        constexpr int    A[]          = {1, 2, 3, 4, 5};
        constexpr size_t size         = 5;
        const auto       optNegNumber = findFirstNegativeNumber(A, size);

        std::cout << (optNegNumber ? optNegNumber.value() : 0) << "\n";
        std::cout << (optNegNumber.has_value() ? optNegNumber.value() : 0) << "\n";
        std::cout << optNegNumber.value_or(0) << "\n";

        std::cout << std::endl;
    }

}  // namespace optional_examples
