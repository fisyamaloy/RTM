#include <iostream>
#include "Examples.hpp"

/*
	SFINAE - substitution failure is not an error. If we have some functions with different /
	parameters but the same name, and, when we try call a function, compiler looks at these /
	functions and substitutes needed types and here SFINAE can happend. Exactly - signature /
	of function can have things which are not correct for needed type.
*/

int main()
{
    SFINAE::example_1();

	return 0;
}
