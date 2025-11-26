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

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, long t_k, std::ofstream *t_outputFile);
void computeMinimalExtensionSerial(ME_Problem &t_P, ME_State t_state);

void clearExtensionsSubsetsWhereMappingExists(const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                              std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);

[[nodiscard]] std::tuple<SI_Problem,
                         SI_State,
                         std::unordered_map<BitVecKey, Matrix>,
                         std::unordered_map<BitVecKey, std::vector<Matrix>>>
prepareArgs_For_SubgraphIsomorphism(const Matrix &t_A1, const Matrix &t_A2);

void subgraphIsomorphismSerial(const SI_Problem                                   &t_P,
                               SI_State                                           &t_state,
                               std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                               std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);

[[nodiscard]] std::tuple<ME_Problem, ME_State>
prepareArgs_For_MinimalExtension(size_t                                                    t_matrixSize,
                                 const std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                                 const std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions,
                                 long                                                      t_k);

[[nodiscard]] std::tuple<std::vector<Matrix>, std::vector<Matrix>>
convertMappingsToResult(const std::unordered_map<BitVecKey, Matrix> &t_mappings);
int computeDistance(const Matrix &t_M1, const Matrix &t_M2);

#endif // EXACT_SOLUTION_INFRA_H
