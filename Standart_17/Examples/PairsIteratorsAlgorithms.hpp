#include <algorithm>
#include <string>
#include <vector>

namespace pia_examples
{
    // copy elements from one structure to another
    void example_1()
    {
        const size_t length = 5;

        int              A[length] = {1, 5, 10, -5, -23};
        std::vector<int> V;
        V.reserve(length);

        std::copy(A, A + length, std::back_inserter(V));
    }

    // move elements from one structure to another
    void example_2()
    {
        std::vector<std::string> A = {"Hello, ", "World"};
        std::vector<std::string> V(A.size());

        // using move algorithm
        std::move(A.begin(), A.end(), V.begin());

        // using move_iterator
        std::copy(std::move_iterator(A.begin()), std::move_iterator(A.end()), V.begin());
    }

    // transform
    void example_3() 
    {
        std::vector<std::string> A = {"Hello ", "World ", "man"};
        std::vector<std::string> B(A.size());
        
        std::transform(A.begin(), A.end(), B.begin(), [&A](const std::string& str) mutable {
            std::string reversedStr = str;
            std::reverse(reversedStr.begin(), reversedStr.end());
            return reversedStr;
        });
    }

}  // namespace pia_examples
