//
// Created by mshamrai on 11/21/25.
//
#include <gtest/gtest.h>
#include "generate_start_cost.h"

class CalculateLabelsMappingCost : public ::testing::Test
{
public:
    std::vector<int> s0 = {0, 1, 0, 0, 4};
    std::vector<int> s1 = {1, 4, 0, 1, 4};
    std::vector<int> s2 = {2, 3, 0, 3, 4};

    std::vector<int> s3 = {0, 2, 0, 2, 4};
    std::vector<int> s4 = {1, 2, 2, 3, 0};
    std::vector<int> s5 = {2, 1, 2, 1, 2};
    std::vector<int> s6 = {3, 0, 1, 0, 1};
};

TEST_F(CalculateLabelsMappingCost, calculate_if_same_class)
{
    std::vector test0 = {0, 1, 0, 0, 4};
    std::vector test1 = {1, 4, 0, 1, 4};
    std::vector test2 = {2, 3, 0, 3, 4};

    int cost0 = calculateCostForTwoLabels(test0, s0);
    int cost1 = calculateCostForTwoLabels(test1, s1);
    int cost2 = calculateCostForTwoLabels(test2, s2);

    ASSERT_EQ(cost0, 0);
    ASSERT_EQ(cost1, 0);
    ASSERT_EQ(cost2, 0);
}

TEST_F(CalculateLabelsMappingCost, calculate_if_not_same_label)
{
    int test_cost_0_1 = calculateCostForTwoLabels(s0, s1);
    int test_cost_0_2 = calculateCostForTwoLabels(s0, s2);
    int test_cost_1_2 = calculateCostForTwoLabels(s1, s2);
    int test_cost_1_0 = calculateCostForTwoLabels(s1, s0);
    int test_cost_2_0 = calculateCostForTwoLabels(s2, s0);
    int test_cost_2_1 = calculateCostForTwoLabels(s2, s1);

    int exact_cost_0_1 = 0;
    int exact_cost_0_2 = 0;
    int exact_cost_1_0 = 4;
    int exact_cost_1_2 = 1;
    int exact_cost_2_0 = 5;
    int exact_cost_2_1 = 2;

    ASSERT_EQ(test_cost_0_1, exact_cost_0_1);
    ASSERT_EQ(test_cost_0_2, exact_cost_0_2);
    ASSERT_EQ(test_cost_1_2, exact_cost_1_2);
    ASSERT_EQ(test_cost_1_0, exact_cost_1_0);
    ASSERT_EQ(test_cost_2_0, exact_cost_2_0);
    ASSERT_EQ(test_cost_2_1, exact_cost_2_1);
}

TEST_F(CalculateLabelsMappingCost, calculate_matrix_of_costs)
{
    auto exact = Matrix {{0, 4, 4, 6},
                            {3, 0, 3, 6},
                            {2, 2, 0, 4},
                            {1, 1, 0, 0}};

    std::map<std::vector<int>, int> labeling = std::map<std::vector<int>, int>();

    labeling.insert(std::pair<std::vector<int>, int>({s3, 0}));
    labeling.insert(std::pair<std::vector<int>, int>({s4, 1}));
    labeling.insert(std::pair<std::vector<int>, int>({s5, 2}));
    labeling.insert(std::pair<std::vector<int>, int>({s6, 3}));

    Matrix test_matrix_of_costs = calculateLabelsMappingCost(labeling);
    for (int i = 0; i < test_matrix_of_costs.rows(); ++i)
        for (int j = 0; j < test_matrix_of_costs.cols(); ++j)
            ASSERT_EQ(test_matrix_of_costs(i, j), exact(i, j));
}


