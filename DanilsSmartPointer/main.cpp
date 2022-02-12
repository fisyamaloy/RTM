#include <iostream>

#include "SharedPointer.hpp"

struct Test
{
    int a;
    char c;

    Test(const int a, const char c) : a(a), c(c) {}

    friend std::ostream& operator<<(std::ostream& out, const Test& test) 
    {
        out << test.a << ' ' << test.c;
        return out;
    }
};

int main()
{
    Danils::SharedPointer<int> sp(new int(5));
    Danils::SharedPointer<int> sp1 = sp;
    Danils::SharedPointer<int> sp2 = sp1;

    std::cout << sp1.use_count() << std::endl;

    auto smartPtrTest = Danils::make_shared<Test>(5, 'd');
    std::cout << *smartPtrTest << std::endl;

    return 0;
}
