#include <iostream>
#include <vector>

#include "Vector.hpp"

int main()
{
    try
    {
        Danils::Vector<int> vec{1, 2, 3, 4, 32};
        vec.reserve(5);
        std::cout << vec.size() << ' ' << vec.capacity() << std::endl;

        for (auto i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i] << std::endl;
        }

        vec.push_front(3202);
        vec.push_front(-10);

        vec.push_back(0);
        vec.push_back(-300);
        vec.push_back(-300);
        vec.push_back(-300);

        for (int i = 0; i < static_cast<int>(vec.size()); ++i)
        {
            std::cout << vec[i] << std::endl;
        }
    }
    catch (const Danils::VectorException& e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
