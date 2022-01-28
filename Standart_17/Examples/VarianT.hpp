#include <iostream>
#include <variant>
#include <string_view>
#include <memory>
/*
std::variant is a class which are based on Union, but variant remembers type it stores. /
Moreover, std::variant can store non-POD-types.
*/
namespace variant_examples
{
    void example_1() 
    {
        std::cout << "example_1:" << std::endl;

        std::variant<int, char, std::string_view> v;
        
        v = 666;
        std::cout << std::get<int>(v) << '\n';

        v = 'J';
        std::cout << std::get<char>(v) << '\n';

        v = std::string_view("Hello, world");
        std::cout << std::get<std::string_view>(v) << '\n';

        std::cout << v.index() << '\n';

        // Throws an exception "bad_variant_access"
        //std::cout << std::get<int>(v) << '\n' << std::endl;
    
        std::cout << std::endl;
    }

    void example_2()
    {
        std::cout << "example_2:" << std::endl;

        std::variant<float, char> v;
        v = 666.99f;
        
        if (std::get_if<char>(&v) != nullptr)
            std::cout << std::get<char>(v) << '\n';
        else if (std::get_if<float>(&v) != nullptr)
            std::cout << std::get<float>(v) << '\n';
    }

}  // namespace variant_examples
