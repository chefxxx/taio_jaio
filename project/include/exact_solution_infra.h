//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EXACT_SOLUTION_INFRA_H
#define EXACT_SOLUTION_INFRA_H

#include "mappings_key.h"
#include "subgraph_isomorphism_args.h"
#include "eigen_port.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, int t_k);
bool checkIsomorphism(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M);
bool addToMappings(const Matrix                            &t_A1,
                   const Matrix                            &t_A2,
                   const Matrix                            &t_M,
                   std::unordered_map<MappingsKey, Matrix> &t_mappings);
void subgraphIsomorphismSerial(const SI_Problem                        &t_P,
                               SI_State                                &t_state,
                               std::unordered_map<MappingsKey, Matrix> &t_mappings);


#endif // EXACT_SOLUTION_INFRA_H
