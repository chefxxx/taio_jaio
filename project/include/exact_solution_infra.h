//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EXACT_SOLUTION_INFRA_H
#define EXACT_SOLUTION_INFRA_H

#include <tuple>

#include "compute_minimal_extension_args.h"
#include "eigen_port.h"
#include "mappings_key.h"
#include "subgraph_isomorphism_args.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, size_t t_k);
void subgraphIsomorphismSerial(const SI_Problem                                   &t_P,
                               SI_State                                           &t_state,
                               std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                               std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);
void saveResultToFile(std::unordered_map<BitVecKey, Matrix> mappings);
void clearExtensionsSubsetsWhereMappingExists(const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                              std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);
void computeMinimalExtensionSerial(ME_Problem &t_P, ME_State t_state);
std::tuple<ME_Problem, ME_State> prepareArgsForMFindingMinimalRun(size_t             t_matrixSize,
                                 const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                 std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions,
                                 int                                                 t_k);

#endif // EXACT_SOLUTION_INFRA_H
