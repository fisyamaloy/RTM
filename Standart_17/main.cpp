#include <iostream>

#include "Examples/FoldExpression.hpp"
#include "Examples/StringView.hpp"
#include "Examples/FileSystem.hpp"

int main()
{
    string_view_examples::example_1();

    fold_expression_examples::example_1();
    fold_expression_examples::example_2();
    fold_expression_examples::example_3();

    file_system_examples::example_1();

    return 0;
}
