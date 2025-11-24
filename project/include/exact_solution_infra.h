//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EXACT_SOLUTION_INFRA_H
#define EXACT_SOLUTION_INFRA_H

#include "eigen_port.h"
#include "mappings_key.h"
#include "subgraph_isomorphism_args.h"

void   performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, int t_k);
bool   checkIsomorphism(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M);
Matrix computeSubgraphFromMapping(const Matrix &t_A1, const Matrix &t_M);
Matrix computeExtension(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M);
void   subgraphIsomorphismSerial(const SI_Problem                                   &t_P,
                                 SI_State                                           &t_state,
                                 std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                                 std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);
void   saveResultToFile(std::unordered_map<BitVecKey, Matrix> mappings);
void   clearExtensionsSubsetsWhereMappingExists(const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                                std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions);
int    computeMinimalExtension(std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions,
                               int                                                 t_numberOfExtensionsToFind);

#endif // EXACT_SOLUTION_INFRA_H
