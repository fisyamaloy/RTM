#include <string_view>

/* 
std::string_view s_w( original, 12); doesn't create copy - O(1),            /
but if we call constructor with 1 param - O(n). It is also immutable class.
*/
namespace string_view_examples
{
    void example_1()
    {
        constexpr size_t LENGTH           = 13;
        char             original[LENGTH] = "Hello, world";

        std::string_view s_w(original, 12); // doesn't create a copy

        std::string s = original;           // creates new copy;

        original[0] = 'J';
        std::cout << "s_w: " << s_w << std::endl;
        std::cout << "s: " << s << std::endl;
    }

}  // namespace string_view_examples
