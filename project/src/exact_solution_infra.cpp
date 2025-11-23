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

    // initialize algorithm variables
    const SI_Problem globalState{t_A1, A2};
    SI_State         initState{cols, M, 0};

    // initialize variables which store solutions
    std::unordered_map<BitVecKey, Matrix> mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // ------------------
    // Run main algorithm
    // ------------------
    spdlog::info("Procedure SubgraphIsomorphismSerial run...");
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);
    // TODO: clear extensions for which keys are inside mappings, this has to be done after
    // TODO: procedure subgraphIsomorphismSerial finished

}

void subgraphIsomorphismSerial(const SI_Problem                                   &t_P,
                               SI_State                                           &t_state,
                               std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                               std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions)
{
    if (t_state.R == t_P.v1) {
        // procedure find or extend run
        const auto key = BitVecKey(t_state.M);
        if (const auto isValid = checkIsomorphism(t_P.A1, t_P.A2, t_state.M)) {
            // add M to solutions
            t_mappings.try_emplace(key, computeSubgraphFromMapping(t_P.A1, t_state.M));
        }
        else {
            // compute extension matrix H and add it to extensions
            if (!t_extensions.contains(key)) {
                t_extensions[key] = {};
            }
            t_extensions[key].push_back(computeExtension(t_P.A1, t_P.A2, t_state.M));
        }
        return;
    }

    for (size_t i = 0; i < t_state.cols.size(); ++i) {
        if (!t_state.cols[i]) {
            // init new state
            t_state.serialNextState(i);
            // recurse
            subgraphIsomorphismSerial(t_P, t_state, t_mappings, t_extensions);
            // back to state
            t_state.serialPrevState(i);
        }
    }
}

bool checkIsomorphism(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    const auto A1prim = t_M * t_A2 * t_M.transpose();
    return (t_A1.array() <= A1prim.array()).all();
}

Matrix computeSubgraphFromMapping(const Matrix &t_A1, const Matrix &t_M) { return t_M.transpose() * t_A1 * t_M; }

Matrix computeExtension(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    auto A2prim = computeSubgraphFromMapping(t_A1, t_M);
    A2prim -= t_A2;
    A2prim = A2prim.cwiseMax(0);
    return A2prim;
}
