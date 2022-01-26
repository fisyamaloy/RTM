#include <iostream>

namespace A
{
    struct C
    {
    };

     void foo([[maybe_unused]] const C& c) { std::cout << "A::C" << std::endl; }
}  // namespace A

void foo([[maybe_unused]] const A::C c) { std::cout << "C" << std::endl; }

int main()
{
    A::C c;
    // foo(c); - ADL error
    /*
        C++ standart says the next: if we call any function with namespaced argument then /
        there is in namespace compiler is looking for the definition of this function.
        Here we have an error, because compiler doesn't know which of the functions should be /
        selected. Below you can see examples how to avoid it.
    */
    A::foo(c);  // if we need a function from namespace     - prefered option
    ::foo(c);   // if we need a function not from namespace - prefered option
    (foo)(c);   // if we need a function not from namespace - not prefered (unreadable)

    return 0;
}
