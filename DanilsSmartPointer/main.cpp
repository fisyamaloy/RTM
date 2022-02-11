#include <iostream>

#include "SharedPointer.hpp"

int main()
{
    Danils::SharedPointer<int> sp(new int(5));
    Danils::SharedPointer<int> sp1 = sp;
    Danils::SharedPointer<int> sp2 = sp1;

    std::cout << sp1.use_count();
    return 0;
}
