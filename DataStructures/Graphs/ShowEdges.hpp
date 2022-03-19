#pragma once
#include <vector>

namespace Graphs
{
    namespace example_1
    {
        const int SIZE          = 4;
        bool      A[SIZE][SIZE] = {
            {0, 1, 0, 1},
            {0, 0, 1, 1},
            {0, 1, 0, 0},
            {1, 0, 1, 0},
        };

        void showEdges()
        {
            std::vector<std::pair<int, int>> duplicatedEdges;
            // Max amount of duplicated edges == SIZE * (SIZE - 1) / 2
            duplicatedEdges.reserve(SIZE * (SIZE - 1) / 2);

            for (int i = 0; i < SIZE; ++i)
            {
                for (int j = 0; j < SIZE; ++j)
                {
                    if (A[i][j] == 1)
                    {
                        if (A[j][i] == 1)  // bidirectional edge
                        {
                            std::cout << i << " <--> " << j << std::endl;
                            duplicatedEdges.emplace_back(j, i);
                            A[j][i] = 0;
                        }
                        else
                        {
                            std::cout << i << " -> " << j << std::endl;
                        }
                    }
                }
            }

            for (auto [column, row] : duplicatedEdges)
            {
                A[column][row] = 1;
            }
        }

        void run() 
        { 
            showEdges(); 
        }

    }  // namespace example_1

}  // namespace Graphs
