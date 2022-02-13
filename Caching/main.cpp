#include <iostream>
#include "SimpleCache.hpp"

int main() 
{   
    auto charCashing = std::make_shared<SimpleCache<char, int>>(2);
    charCashing->putItem('a', std::make_shared<int>(5));
    charCashing->putItem('b', std::make_shared<int>(6));
    charCashing->putItem('c', std::make_shared<int>(7));
	

	return 0;
}
