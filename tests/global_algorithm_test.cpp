//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#include <gtest/gtest.h>

#include "exact_solution_infra.h"

class ExactSolutionTest : public ::testing::Test
{
protected:
    static std::tuple<SI_Problem, SI_State, std::unordered_map<BitVecKey, Matrix>, std::unordered_map<BitVecKey, std::vector<Matrix>>>
    prepareTestForGraphs(const Matrix &A1, const Matrix &A2)
    {

        Matrix M(A1.rows(), A2.rows());
        M.setZero();

        const std::vector cols(M.cols(), false);
        const SI_Problem SI_global{A1, A2};
        const SI_State SI_init{cols, M, 0};

        std::unordered_map<BitVecKey, Matrix>              mappings;
        std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

        return std::make_tuple(SI_global, SI_init, mappings, extensions);
    }
};

TEST_F(ExactSolutionTest, smallGraphs)
{
    const auto A1 = Matrix{{0, 1, 0}, {0, 0, 2}, {3, 0, 0}};
    const auto A2 = Matrix{{0, 0, 0, 0}, {4, 0, 3, 0}, {0, 0, 0, 1}, {0, 2, 0, 0}};

    auto [globalState, initState, mappings, extensions] = prepareTestForGraphs(A1, A2);
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

    auto [globalState, initState] = prepareArgs_For_SubgraphIsomorphism(A1, A2);

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

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

    auto [globalState, initState] = prepareArgs_For_SubgraphIsomorphism(G3, G4);

    // variables to store results of computation
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // run
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);

    // just sanity check
    ASSERT_EQ(mappings.size(), 0);

    auto [globalStateMinAlg, startingState] = prepareArgs_For_MinimalExtension(G4.rows(), mappings, extensions, 1);
    computeMinimalExtensionSerial(globalStateMinAlg, startingState);

    std::cout << globalStateMinAlg.global.graph << '\n';
}