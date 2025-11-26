//
// Created by chefxx on 13.11.2025.
//

#include <gtest/gtest.h>
#include "generate_start_cost.h"

class GetNeighbors : public ::testing::Test
{
public:
    Matrix A1;
    Matrix A2;
    Matrix A3;
    std::vector<std::vector<int>> exact_resultsA1;
    std::vector<std::vector<int>> exact_resultsA2;

protected:
    void SetUp() override
    {
        A1 = Matrix{{0, 2},
                        {1, 3}};

        A2 = Matrix{{3, 2, 0},
                        {0, 0, 1},
                        {1, 2, 0}};

        A3 = Matrix{{0, 2, 3},
                        {4, 0, 1},
                        {5, 6, 0}};
    }
};

TEST_F(GetNeighbors, find_out_in_neighbors_forEachVertex)
{
    std::vector<std::vector<int>> exact_resultsA1 = std::vector<std::vector<int>>();
    std::vector<std::vector<int>> exact_resultsA2 = std::vector<std::vector<int>>();
    std::vector<std::vector<int>> exact_A3_out = {
        {1, 2},
        {0, 2},
        {0, 1},
    };

    std::vector<std::vector<int>> exact_A3_in = {
        {1, 2},
        {0, 2},
        {0, 1},
    };

    std::vector<std::vector<int>> test_resultsA1 = std::vector<std::vector<int>>();
    std::vector<std::vector<int>> test_resultsA2 = std::vector<std::vector<int>>();
    // For A1

    exact_resultsA1.push_back(std::vector<int>({1}));
    exact_resultsA1.push_back(std::vector<int>({1}));
    exact_resultsA1.push_back(std::vector<int>({0, 1}));
    exact_resultsA1.push_back(std::vector<int>({0, 1}));
    // For A2

    exact_resultsA2.push_back(std::vector<int>({0, 1}));
    exact_resultsA2.push_back(std::vector<int>({0, 2}));
    exact_resultsA2.push_back(std::vector<int>({2}));
    exact_resultsA2.push_back(std::vector<int>({0, 2}));
    exact_resultsA2.push_back(std::vector<int>({0, 1}));
    exact_resultsA2.push_back(std::vector<int>({1}));

    test_resultsA1.push_back(getIndicesOfOutNeighbors(A1, 0));
    test_resultsA1.push_back(getIndicesOfInNeighbors(A1, 0));
    test_resultsA1.push_back(getIndicesOfOutNeighbors(A1, 1));
    test_resultsA1.push_back(getIndicesOfInNeighbors(A1, 1));

    test_resultsA2.push_back(getIndicesOfOutNeighbors(A2, 0));
    test_resultsA2.push_back(getIndicesOfInNeighbors(A2, 0));
    test_resultsA2.push_back(getIndicesOfOutNeighbors(A2, 1));
    test_resultsA2.push_back(getIndicesOfInNeighbors(A2, 1));
    test_resultsA2.push_back(getIndicesOfOutNeighbors(A2, 2));
    test_resultsA2.push_back(getIndicesOfInNeighbors(A2, 2));

    for (int i = 0; i < exact_resultsA1.size(); ++i) {
        for (int j = 0; j < exact_resultsA1[i].size(); ++j) {
            ASSERT_EQ(exact_resultsA1[i][j], test_resultsA1[i][j]);
        }
    }

    for (int i = 0; i < exact_resultsA2.size(); ++i) {
        for (int j = 0; j < exact_resultsA2[i].size(); ++j) {
            ASSERT_EQ(exact_resultsA2[i][j], test_resultsA2[i][j]);
        }
    }

    for (int i = 0; i < 3; ++i) {
        auto outN = getIndicesOfOutNeighbors(A3, i);
        auto inN  = getIndicesOfInNeighbors(A3, i);

        ASSERT_EQ(outN.size(), exact_A3_out[i].size());
        ASSERT_EQ(inN.size(),  exact_A3_in[i].size());

        for (int j = 0; j < outN.size(); ++j)
            ASSERT_EQ(outN[j], exact_A3_out[i][j]);

        for (int j = 0; j < inN.size(); ++j)
            ASSERT_EQ(inN[j], exact_A3_in[i][j]);
    }
}
TEST_F(GetNeighbors, number_of_in_and_out_neighbors)
{
    std::vector expected_A1_out = {1, 2};
    std::vector expected_A1_in  = {1, 2};

    std::vector expected_A2_out = {2, 1, 2};
    std::vector expected_A2_in  = {2, 2, 1};

    std::vector expected_A3_out = {2, 2, 2};
    std::vector expected_A3_in  = {2, 2, 2};

    auto test_resultsA1_out = getNumberOfOutNeighbors(A1);
    auto test_resultsA1_in = getNumberOfInNeighbors(A1);
    auto test_resultsA2_out = getNumberOfOutNeighbors(A2);
    auto test_resultsA2_in = getNumberOfInNeighbors(A2);
    auto test_resultsA3_out = getNumberOfOutNeighbors(A3);
    auto test_resultsA3_in = getNumberOfInNeighbors(A3);


    for (int i = 0; i < expected_A1_out.size(); ++i) {
        ASSERT_EQ(expected_A1_out[i], test_resultsA1_out[i]);
        ASSERT_EQ(expected_A1_in[i], test_resultsA1_in[i]);
    }
    for (int i = 0; i < expected_A2_out.size(); ++i) {
        ASSERT_EQ(expected_A2_out[i], test_resultsA2_out[i]);
        ASSERT_EQ(expected_A2_in[i],  test_resultsA2_in[i]);
    }

    for (int i = 0; i < expected_A3_out.size(); ++i) {
        ASSERT_EQ(expected_A3_out[i], test_resultsA3_out[i]);
        ASSERT_EQ(expected_A3_in[i],  test_resultsA3_in[i]);
    }
}