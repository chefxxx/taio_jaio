//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include "exact_solution_infra.h"
#include "common.h"

#include <spdlog/spdlog.h>

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
    subgraphIsomorphismSerial(globalState, initState);
}

void subgraphIsomorphismSerial(const SI_Problem &P, SI_State &state)
{
    spdlog::info("Procedure SubgraphIsomorphismParallel run...");
    if (state.R == P.v1) {
        // procedure find or extend run
        return;
    }

    for (int i = 0; i < state.cols.size(); ++i) {
        if (!state.cols[i]) {
            // init new state
            state.serialNextState(i);
            // recurse
            subgraphIsomorphismSerial(P, state);
            // back to state
            state.serialPrevState(i);
        }
    }
}
