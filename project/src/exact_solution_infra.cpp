//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include "exact_solution_infra.h"

#include <iostream>
#include <spdlog/spdlog.h>

#include "common.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, const int t_k)
{
    spdlog::info("Preparing exact algorithm run...");

    // -----------------------
    // Prepare input variables
    // -----------------------
    const long v1 = t_A1.rows();
    Matrix     A2 = t_A2;
    long       v2 = A2.rows();

    // the case where we need to add isolated vertices to A2
    v2 = completeVerticesNumber(v1, v2, t_k);
    if (v2 > A2.rows())
        extendVertices(A2, v2);

    // initialize matrix M
    Matrix M(v1, v2);
    M.setZero();

    // initialize cols set
    const std::vector<bool> cols(M.cols());

    // ------------------
    // Run main algorithm
    // ------------------
    const SI_Problem globalState{t_A1, A2};
    SI_State initState{cols, M, 0};
    spdlog::info("Procedure SubgraphIsomorphismSerial run...");
    subgraphIsomorphismSerial(globalState, initState);
}

void subgraphIsomorphismSerial(const SI_Problem &t_P, SI_State &t_state)
{
    if (t_state.R == t_P.v1) {
        // procedure find or extend run
        std::cout << t_state.M << '\n';
        return;
    }

    for (size_t i = 0; i < t_state.cols.size(); ++i) {
        if (!t_state.cols[i]) {
            // init new state
            t_state.serialNextState(i);
            // recurse
            subgraphIsomorphismSerial(t_P, t_state);
            // back to state
            t_state.serialPrevState(i);
        }
    }
}

void findOrExtend(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    bool isValid = true;
    const auto A1prim = t_M * t_A2 * t_M.transpose();
    for (long i = 0; i < t_A1.rows(); ++i) {
        for (long j = 0; j < t_A1.cols(); ++j) {
            if (t_A1(i, j) > A1prim(i,j)) {
                isValid = false;
                break;
            }
        }
        if (!isValid) {
            break;
        }
    }
}
