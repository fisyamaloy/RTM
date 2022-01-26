#include <any>
#include <iostream>
#include <string_view>

/*
Any is a class which can store anything and doesn't store type information 
*/
namespace any_examples
{
    void example_1()
    {
        std::cout << "example_1:" << std::endl;

        std::any obj;
        obj = 100;
        std::cout << std::any_cast<int>(obj) << "\n";

        obj = "Hello, world";
        std::cout << std::any_cast<const char*>(obj) << "\n";

        struct Tag
        {
            int                             ref       = -1;
            std::optional<std::string_view> attribute = {};
        } tag{666, std::make_optional("Hello world!!!")};
        obj = tag;
        const auto tagFromAny = std::any_cast<Tag>(obj);
        std::cout << tagFromAny.attribute.value();

        std::cout << std::endl;
    }

}  // namespace any_examples
