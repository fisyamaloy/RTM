#include <iostream>
#include <vector>

#include "Vector.hpp"

int main()
{

    try
    {
        Danils::Vector<int> vec = {100, 1, -1, -25, 100, -200, 400, 333, 0};
        
        for (auto i = 0; i < vec.size(); ++i)
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
