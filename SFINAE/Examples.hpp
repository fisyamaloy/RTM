#pragma once
#include <iostream>

namespace SFINAE
{
    template<class T>
    typename T::some_type foo(T)
    {
        std::cout << "foo(T)\n";

        return typename T::some_type();
    }

    template <class...>
    int foo(...)
    {
        std::cout << "foo(...)\n";

        return 1;
    }

    void example_1() 
    {
        foo(5);
    }

}  // namespace SFINAE
