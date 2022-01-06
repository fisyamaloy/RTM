#include <iostream>
#include "MemAllocChecker.hpp"

struct S
{
    char a;
    int b;
    double d1;
    char c;
    double d2;
};

int main() 
{
    std::cout << sizeof(S) << std::endl;
    
	return 0;
}
