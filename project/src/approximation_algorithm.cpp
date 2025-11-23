//
// Created by mshamrai on 11/23/25.
//

#include "approximation_algorithm.h"
#include "generate_start_cost.h"
#include "hungarian_method.h"
#include "upgrade_cost_function.h"

Matrix approximationAlgorithm(const Matrix &graph_1, const Matrix &graph_2)
{
    auto startCost = generateStartCost(graph_1, graph_2);
    auto startMapping = hungarianMethod(startCost.cast<double>());
    auto mappingVector = getVectorOfMappingsFromMatrix(startMapping);
    auto updatedCost = upgradeCostFunction(startCost.cast<double>(), mappingVector, graph_1, graph_2);
    auto updatedMapping = hungarianMethod(updatedCost.cast<double>());
    return checkIsomorphism(graph_1, graph_2, updatedMapping) ?
    graph_2 : graph_2 + computeExtension(graph_1, graph_2, updatedMapping);
}