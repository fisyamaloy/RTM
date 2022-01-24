#include <iostream>

// Fold is a function, which applies a combination to sequential elements-pairs and /
// returns some result.
namespace fold_expression_examples
{
	// example of input: 1,2,3,5,8.
	// how it works:
	// 1 step - 3 + 3,5,8;
	// 2 step - 6 + 5,8;
	// 3 step - 11 + 8;
	// 4 step - 19.
	void example_1() 
	{
        auto sum = [](const auto... sequence) {
			return (... + sequence);
        };
		std::cout << sum(-5, 5, 0, 4, 3, 3) << std::endl;
	}

	template<class Func, class... T>
	void call(Func function, T&&... seq)
    {
		(function(seq), ...);
	}

	// Call the passed function with each of the passed elements of sequence.
	void example_2() 
	{
		call([](auto v) {std::cout << v << " ";}, 
			5, 4, " <--> ", "END");

		endl(std::cout); // ADL =)
	}

	template <class... T>
    bool areElemsPositive(const T&... args)
    {
        return ((args > 0) && ...);
    }

	void example_3() 
	{
		std::cout << (areElemsPositive(5, 10, 13) ? "Yes" : "No") << std::endl;
		std::cout << (areElemsPositive(5, 10, -723, 13) ? "Yes" : "No") << std::endl;
	}

}  // namespace fold_expressions_examples
