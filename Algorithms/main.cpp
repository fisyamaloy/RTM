#include <iostream>
#include <vector>

#include "BinarySearch.hpp"

int main() 
{ 
	std::vector<int> A = {-10, -4, -3, -1, 0, 1, 15};

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
