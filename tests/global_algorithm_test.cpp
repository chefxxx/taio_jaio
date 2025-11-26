//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#include <gtest/gtest.h>

#include "exact_solution_infra.h"

TEST(ExactSolutionTest, smallGraphs)
{
    const auto A1 = Matrix{{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    const auto A2 = Matrix{{0, 0, 0, 0}, {4, 0, 3, 0}, {0, 0, 0, 1}, {0, 2, 0, 0}};

    // initialize matrix M
    Matrix M(3, 4);
    M.setZero();

    // columns set
    const std::vector<bool> cols(M.cols());

    // init alg variables
    const SI_Problem globalState{A1, A2};
    SI_State         initState{cols, M, 0};

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // check if sizes match
    // TODO: add check for extensions
    ASSERT_EQ(mappings.size(), 1);

    const auto expectedMapping  = Matrix{{{0, 0, 1, 0}, {0, 0, 0, 1}, {0, 1, 0, 0}}};
    const auto expectedSubgraph = Matrix{{{0, 0, 0, 0}, {0, 0, 3, 0}, {0, 0, 0, 1}, {0, 2, 0, 0}}};
    ASSERT_EQ(expectedMapping, mappings.begin()->first.M);
    ASSERT_EQ(expectedSubgraph, mappings.begin()->second);

    clearExtensionsSubsetsWhereMappingExists(mappings, extensions);
    ASSERT_FALSE(extensions.contains(mappings.begin()->first));

    // TODO: check if extensions are correct
}

TEST(ExactSolutionTest, smallGraphsExtensionTest)
{
    const auto A1 = Matrix{{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}}};
    const auto A2 = Matrix{{{0, 0, 0, 0, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 0}, {0, 0, 0, 0, 1}, {0, 1, 0, 0, 0}}};

    auto [globalState, initState] = prepareArgs_For_MinimalExtension(A1.rows(), A2.rows(), A1, A2);

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // just sanity check
    ASSERT_EQ(mappings.size(), 1);

    auto [globalStateMinAlg, startingState] = prepareArgs_For_SubgraphIsomorphism(A2.rows(), mappings, extensions, 3);
    computeMinimalExtensionSerial(globalStateMinAlg, startingState);

    auto expected = Matrix{{0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 0}};

    ASSERT_EQ(expected, globalStateMinAlg.global.graph);
}

TEST(ExactSolutionTest, MichalFavouriteGraphs)
{
    const Matrix G3{{0, 1, 1, 0, 0}, {1, 0, 0, 1, 0}, {1, 0, 0, 1, 1}, {0, 1, 1, 0, 1}, {0, 0, 1, 1, 0}};

    const Matrix G4{{0, 1, 0, 1, 0, 0, 0, 0},
                    {1, 0, 1, 0, 0, 0, 0, 0},
                    {0, 1, 0, 1, 0, 1, 0, 0},
                    {1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 0, 0, 1},
                    {0, 0, 1, 0, 0, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1, 0, 1},
                    {0, 0, 0, 0, 1, 0, 1, 0}};

    auto [globalState, initState] = prepareArgs_For_MinimalExtension(G3.rows(), G4.rows(), G3, G4);

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // just sanity check
    ASSERT_EQ(mappings.size(), 0);

    auto [globalStateMinAlg, startingState] = prepareArgs_For_SubgraphIsomorphism(G4.rows(), mappings, extensions, 1);
    computeMinimalExtensionSerial(globalStateMinAlg, startingState);

    std::cout << globalStateMinAlg.global.graph << '\n';
}