//
// Created by mshamrai on 11/23/25.
//

#include "generate_start_cost.h"
#include "gtest/gtest.h"
#include "hungarian_method.h"
#include "upgrade_cost_function.h"
class UpdateCostAfterHungarianTest : public ::testing::Test
{
public:
    Matrix G1 {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};

    Matrix G2 {
        {0, 1, 0, 1},
           {1, 0, 1, 0},
           {1, 1, 0, 1},
           {0, 0, 1, 0}};
};

TEST_F (UpdateCostAfterHungarianTest, update_costs_after_all_flow_square_matrix)
{
    auto startCost = generateStartCost(G1, G2);
    auto expandedStartCost = addZeroColumnAndZeroRowToMatrix(startCost);
    auto startMapping = hungarianMethod(expandedStartCost.cast<double>());
    auto mappingVector = getVectorOfMappingsFromMatrix(startMapping);
    auto updatedCost = upgradeCostFunction(startCost.cast<double>(), mappingVector, G1, G2);
    for (int i = 0; i < mappingVector.size(); ++i) {
        printf("%f ", updatedCost(i, mappingVector[i]));
    }
}