//
// Created by mshamrai on 11/23/25.
//

#include <common.h>

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

    Matrix G3 {{0, 1, 1, 0, 0},
                    {1, 0, 0, 1, 0},
                    {1, 0, 0, 1, 1},
                    {0, 1, 1, 0, 1},
                    {0, 0, 1, 1, 0}};

    Matrix G4 {{0, 1, 0, 1, 0, 0, 0, 0},
                    {1, 0, 1, 0, 0, 0, 0, 0},
                    {0, 1, 0, 1, 0, 1, 0, 0},
                    {1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 0, 0, 1},
                    {0, 0, 1 ,0, 0, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1, 0, 1},
                    {0, 0, 0, 0, 1, 0, 1, 0},};
};

TEST_F (UpdateCostAfterHungarianTest, update_costs_after_all_flow_square_matrix)
{
    auto startCost = generateStartCost(G1, G2);
    auto startMapping = hungarianMethod(startCost.cast<double>().eval());
    auto mappingVector = getVectorOfMappingsFromMatrix(startMapping);
    auto updatedCost = upgradeCostFunction(startCost.cast<double>().eval(), mappingVector, G1, G2);
    auto updatedMapping = hungarianMethod(updatedCost.cast<double>().eval());
}

TEST_F (UpdateCostAfterHungarianTest, update_costs_after_all_flow_rect_matrix)
{
    auto startCost = generateStartCost(G3, G4);
    auto startMapping = hungarianMethod(startCost.cast<double>().eval());
    auto mappingVector = getVectorOfMappingsFromMatrix(startMapping);
    auto updatedCost = upgradeCostFunction(startCost.cast<double>().eval(), mappingVector, G1, G2);
    auto updatedMapping = hungarianMethod(updatedCost.cast<double>().eval());
    auto updatedMappingVector = getVectorOfMappingsFromMatrix(updatedMapping);
}