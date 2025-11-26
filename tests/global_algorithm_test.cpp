//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#include <gtest/gtest.h>

#include "exact_solution_infra.h"


TEST(ExactSolutionTest, smallGraphs)
{
    const auto A1 = Matrix{{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    const auto A2 = Matrix{{0, 0, 0, 0}, {4, 0, 3, 0}, {0, 0, 0, 1}, {0, 2, 0, 0}};

    auto [globalState, initState, mappings, extensions] = prepareArgs_For_SubgraphIsomorphism(A1, A2);
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);
    const auto [resMaps, resGraphs] = convertMappingsToResult(mappings);
    ASSERT_EQ(resGraphs.size(), resMaps.size());
    ASSERT_EQ(resGraphs.size(), 1);

    const auto expectedMapping  = Matrix{{{0, 0, 1, 0}, {0, 0, 0, 1}, {0, 1, 0, 0}}};
    const auto expectedSubgraph = Matrix{{{0, 0, 0, 0}, {0, 0, 3, 0}, {0, 0, 0, 1}, {0, 2, 0, 0}}};
    ASSERT_EQ(resGraphs[0], expectedSubgraph);
    ASSERT_EQ(resMaps[0], expectedMapping);

    clearExtensionsSubsetsWhereMappingExists(mappings, extensions);
    ASSERT_FALSE(extensions.contains(mappings.begin()->first));

    // TODO: check if extensions are correct
}

TEST(ExactSolutionTest, smallGraphsExtensionTest)
{
    const auto A1 = Matrix{{{0, 1, 0}, {0, 0, 1}, {1, 0, 0}}};
    const auto A2 = Matrix{{{0, 0, 0, 0, 0}, {1, 0, 0, 1, 0}, {0, 1, 0, 0, 0}, {0, 0, 0, 0, 1}, {0, 1, 0, 0, 0}}};

    auto [globalState, initState, mappings, extensions] = prepareArgs_For_SubgraphIsomorphism(A1, A2);

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // just sanity check
    ASSERT_EQ(mappings.size(), 1);

    auto [globalStateMinAlg, startingState] = prepareArgs_For_MinimalExtension(A2.rows(), mappings, extensions, 3);
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

    auto [globalState, initState, mappings, extensions] = prepareArgs_For_SubgraphIsomorphism(G3, G4);

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // just sanity check
    ASSERT_EQ(mappings.size(), 0);

    auto [globalStateMinAlg, startingState] = prepareArgs_For_MinimalExtension(G4.rows(), mappings, extensions, 1);
    computeMinimalExtensionSerial(globalStateMinAlg, startingState);

    std::cout << globalStateMinAlg.global.graph << '\n';
}