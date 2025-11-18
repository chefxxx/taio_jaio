//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <set>
#include <spdlog/spdlog.h>

#include "exact_solution_infra.h"
#include "common.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, const int t_k)
{
    spdlog::info("Preparing exact algorithm run...");

    // -----------------------
    // Prepare input variables
    // -----------------------
    const Matrix A1 = t_A1;
    const int    v1 = A1.rows();
    Matrix       A2 = t_A2;
    int          v2 = A2.rows();

    // the case where we need to add isolated vertices to A2
    v2 = completeVerticesNumber(v1, v2, t_k);
    if (v2 > A2.rows())
        extendVertices(A2, v2);

    // ------------------
    // Run main algorithm
    // ------------------
}
