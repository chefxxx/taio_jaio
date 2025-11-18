//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EXACT_SOLUTION_INFRA_H
#define EXACT_SOLUTION_INFRA_H

#include "eigen_port.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, int t_k);
void subgraphIsomorphism(std::set<long> t_cols, long t_R, Matrix t_A1, Matrix t_A2, Matrix t_M);

#endif // EXACT_SOLUTION_INFRA_H
