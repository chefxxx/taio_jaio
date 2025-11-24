//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#include <gtest/gtest.h>

#include "exact_solution_infra.h"

TEST(ExactSolutionTest, smallGraphs)
{
    const auto A1 = Matrix{
    {0, 1, 0},
        {0, 0, 2},
        {3, 0, 0}
    };
    const auto A2 = Matrix{
    {0, 0, 0, 0},
        {4, 0, 3, 0},
        {0, 0, 0, 1},
        {0, 2, 0, 0}
    };

    // initialize matrix M
    Matrix M(3, 4);
    M.setZero();

    // columns set
    const std::vector<bool> cols(M.cols());

    // init alg variables
    const SI_Problem globalState{A1, A2};
    SI_State         initState{cols, M, 0};

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix> mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    ASSERT_EQ(mappings.size(), 1);
    const auto expectedMapping = Matrix{
        {
                {0, 0, 1, 0},
                {0, 0, 0, 1},
                {0, 1, 0, 0}
            }};
    const auto expectedSubgraph = Matrix{
        {
                {0, 0, 0, 0},
                {0, 0, 3, 0},
                {0, 0, 0, 1},
                {0, 2, 0, 0}
            }};
    ASSERT_EQ(expectedMapping, mappings.begin()->first.M);
    ASSERT_EQ(expectedSubgraph, mappings.begin()->second);

    // TODO: check if extensions are correct
    for (const auto& [key, list] : extensions) {
        std::cout << "For subset: ";
        for (const auto& elem : key.bits)
            std::cout << elem;
        std::cout << "\n\n";
        for (const auto& extension : list) {
            std::cout << extension << "\n\n";
        }
    }
}