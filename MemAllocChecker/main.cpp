#include <iostream>
#include "MemAllocChecker.hpp"

struct Taxi : Danils::MemoryAllocationChecker
{
    char* name;
    int* number;
};

int main() 
{
    std::cout << Danils::usedMemory << std::endl;
    Taxi* taxi_1 = new Taxi[5];
    for (int i = 0; i < 5; ++i)
    {
        taxi_1->number = new int(3);
    }

    std::cout << Danils::usedMemory << std::endl;
    delete[] taxi_1;
    
    std::cout << Danils::usedMemory << std::endl;

	return 0;
}