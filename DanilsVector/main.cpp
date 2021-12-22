#include <iostream>
#include <vector>

#include "Vector.hpp"

int main()
{
    std::vector<int> a(5);
    a.push_back(4);
    try
    {
        Danils::Vector<int> vec(5);
        vec.push_back(4);
        vec.reserve(7);
        std::cout << vec.size() << ' ' << vec.capacity() << std::endl;

        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i] << std::endl;
        }

        vec.erase(2);

        for (size_t i = 0; i < vec.size(); ++i)
        {
            std::cout << vec[i] << std::endl;
        }
    }
    catch (const Danils::VectorException& e)
    {
        std::cout << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cout << "asd" << e.what() << std::endl;
    }

    return 0;
}
