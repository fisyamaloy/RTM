#include <exception>
#include <iostream>
#include <stdexcept>
#include <thread>
#include "Asynchrony.hpp"

/*
    C++11 introduced the exception_ptr type that allows to transport exceptions between threads.
    If we have multiple worker threads, we will need to keep one exception_ptr
    for each of them.

    Note that exception_ptr is a shared ptr-like pointer, so you will need to keep at least one
    exception_ptr pointing to each exception or they will be released.
*/
std::exception_ptr extPtr = nullptr;

void foo()
{
    try
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        throw std::runtime_error("to be passed between threads");
    }
    catch (...)
    {
        extPtr = std::current_exception();
    }
}

int main()
{
    Asynchrony::example_1();
    Asynchrony::example_2();
    Asynchrony::example_3();

    return 0;
}
