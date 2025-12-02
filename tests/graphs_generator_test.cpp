//
// Created by mshamrai on 12/1/25.
//

#include <gtest/gtest.h>

#include "graphs_generator.h"

TEST(GenerateGraphsTest, fromOneToTenVertices)
{
    for (int i = 1; i < 11; ++i) {
        int minM = i;
        int maxM = i;
        int maxMult = 12;
        std::pair<Matrix, Matrix> graphs = generateTwoGraphs(minM, maxM, maxMult);
        auto G1 = graphs.first;
        auto G2 = graphs.second;
        ASSERT_EQ(G2.rows(), G2.cols());
        ASSERT_LE(G2.rows(), maxM);
        ASSERT_LE(G2.rows(), G1.rows());
        for (unsigned j = 0; j < G2.rows(); ++j) {
            for (unsigned k = 0; k < G2.cols(); ++k) {
                ASSERT_LE(G2(j,k), maxMult);
            }
        }

        ASSERT_EQ(G1.rows(), G1.cols());
        ASSERT_LE(G1.rows(), maxM);
        for (unsigned j = 0; j < G1.rows(); ++j) {
            for (unsigned k = 0; k < G1.cols(); ++k) {
                ASSERT_LE(G1(j,k), maxMult);
            }
        }
    }
}

TEST(GenerateGraphsTest, GraphsFromTwoSameSeeds)
{
    unsigned int seed = 14141;
    unsigned int minM = 10;
    unsigned int maxM = 100;
    unsigned int maxMult = 100;
    auto firstPair = generateTwoGraphs(minM, maxM, maxMult, seed);
    auto secondPair = generateTwoGraphs(minM, maxM, maxMult, seed);

    ASSERT_EQ(firstPair.first, secondPair.first);
    ASSERT_EQ(firstPair.second, secondPair.second);
}

TEST(GenerateGraphsTest, GraphsFromTwoDifferentSeeds)
{
    unsigned int minM = 10;
    unsigned int maxM = 100;
    unsigned int maxMult = 100;
    auto firstPair = generateTwoGraphs(minM, maxM, maxMult);
    auto secondPair = generateTwoGraphs(minM, maxM, maxMult);

    ASSERT_NE(firstPair.first, secondPair.first);
    ASSERT_NE(firstPair.second, secondPair.second);
}