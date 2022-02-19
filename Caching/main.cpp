#include <iostream>
#include "SimpleCache.hpp"

int main() 
{   
    auto charCashing = std::make_shared<SimpleCache<char, int>>(2);
    {
        auto asp = std::make_shared<int>(5);

        charCashing->putItem('c', std::move(asp));

        auto s_p = charCashing->getItem('c');
        std::cout << *s_p << std::endl;
    }
    auto s_p = charCashing->getItem('c');

    if (!s_p)
    {
        std::cout << "expired";
    }

	return 0;
}
