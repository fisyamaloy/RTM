#pragma once
#include <exception>
#include <future>
#include <iostream>
#include <stdexcept>
#include <thread>

namespace Asynchrony
{
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

    /*
        C++11 introduced the exception_ptr type that allows to transport exceptions between
       threads. If we have multiple worker threads, we will need to keep one exception_ptr for
       each of them.

        Note that exception_ptr is a shared ptr-like pointer, so you will need to keep at least
       one exception_ptr pointing to each exception or they will be released.
    */
    void example_1()
    {
        std::thread thr(foo);
        thr.join();

        if (extPtr != nullptr)
        {
            try
            {
                std::rethrow_exception(extPtr);
            }
            catch (const std::exception& e)
            {
                std::cerr << "Thread existed with exception: " << e.what() << std::endl;
            }
        }
    }

    bool foo_throw() { throw std::runtime_error("to be passed between threads"); }

    // Parent thread waits when we get result from future.get()
    void example_2()
    {
        auto futureWork = std::async(std::launch::async, foo_throw);

        try
        {
            const bool b = futureWork.get();
            std::cout << b << std::endl;
        }
        catch (const std::exception& e)
        {
            std::cerr << "Thread existed with exception: " << e.what() << std::endl;
        }
    }

    void isEven(const int number, std::promise<bool>&& promise)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        promise.set_value(number % 2 == 0);
    }

    void example_3()
    {
        std::promise<bool> promise;
        auto               futureIsEven = promise.get_future();
        
        std::thread workThread(isEven, 3, std::move(promise)); // after this it will work asynk

        std::this_thread::sleep_for(std::chrono::seconds(3));

        std::cout << futureIsEven.get() << std::endl;
        workThread.join();
    }

}  // namespace Asynchrony
