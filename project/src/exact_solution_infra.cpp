//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <iostream>
#include <spdlog/spdlog.h>

#include "exact_solution_infra.h"
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

    // initialize algorithm variables
    const SI_Problem globalState{t_A1, A2};
    SI_State         initState{cols, M, 0};

    // initialize variables which store solutions
    std::unordered_map<BitVecKey, Matrix> mappings;

    // ------------------
    // Run main algorithm
    // ------------------
    spdlog::info("Procedure SubgraphIsomorphismSerial run...");
    subgraphIsomorphismSerial(globalState, initState, mappings);
}

void subgraphIsomorphismSerial(const SI_Problem                        &t_P,
                               SI_State                                &t_state,
                               std::unordered_map<BitVecKey, Matrix> &t_mappings)
{
    if (t_state.R == t_P.v1) {
        // procedure find or extend run
        if (const auto isValid = checkIsomorphism(t_P.A1, t_P.A2, t_state.M)) {
            // add M to solutions
            t_mappings.try_emplace(BitVecKey(t_state.M), computeSubgraphFromMapping(t_P.A1, t_state.M));
        }
        else {
            // compute extension matrix H
        }
        return;
    }

    for (size_t i = 0; i < t_state.cols.size(); ++i) {
        if (!t_state.cols[i]) {
            // init new state
            t_state.serialNextState(i);
            // recurse
            subgraphIsomorphismSerial(t_P, t_state, t_mappings);
            // back to state
            t_state.serialPrevState(i);
        }
    }
}

bool checkIsomorphism(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    const auto A1prim = t_M * t_A2 * t_M.transpose();
    for (long i = 0; i < t_A1.rows(); ++i) {
        for (long j = 0; j < t_A1.cols(); ++j) {
            if (t_A1(i, j) > A1prim(i, j))
                return false;
        }
    }
    return true;
}

Matrix computeSubgraphFromMapping(const Matrix &t_A1, const Matrix &t_M)
{
    return t_M.transpose() * t_A1 * t_M;
}

Matrix computeExtension(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    auto A2prim = computeSubgraphFromMapping(t_A1, t_M);
    assert(A2prim.rows() == t_A2.rows());
    assert(A2prim.cols() == t_A2.cols());
    for (long i = 0; i < t_A2.rows(); ++i) {
        for (long j = 0; j < t_A2.cols(); ++j) {
            A2prim(i,j) = std::max(A2prim(i,j) - t_A2(i,j), 0);
        }
    }
    return A2prim;
}
