//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <spdlog/spdlog.h>

#include "exact_solution_infra.h"
#include "common.h"

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, size_t t_k)
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
    std::unordered_map<BitVecKey, Matrix>              mappings;
    std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;

    // ------------------
    // Run main algorithm
    // ------------------
    spdlog::info("Procedure SubgraphIsomorphismSerial run...");
    subgraphIsomorphismSerial(globalState, initState, mappings, extensions);
    // TODO: clear extensions for which keys are inside mappings, this has to be done after
    // TODO: procedure subgraphIsomorphismSerial finished

    // -----------------------------------------
    // Return mappings when extension not needed
    // -----------------------------------------
    if (mappings.size() >= t_k) {
        // saveResultToFile(mappings);
    }

    // -------------------------------------
    // Clear extensions where mapping exists
    // -------------------------------------
    clearExtensionsSubsetsWhereMappingExists(mappings, extensions);

    // ----------------------
    // Find minimal extension
    // ----------------------
    const int numberOfExtensionsToFind = t_k - mappings.size();

    // ----------------------
    // Return combined result
    // ----------------------
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

void clearExtensionsSubsetsWhereMappingExists(const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                              std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions)
{
    for (auto it = t_mappings.begin(); it != t_mappings.end(); ++it) { // for all subsets that have mappings
        if (t_extensions.contains(it->first)) {
            t_extensions.erase(it->first);
        }
    }
}

void computeMinimalExtensionSerial(ME_Problem &t_P, ME_State t_state)
{
    if (t_state.numberOfExtensionsToFind == 0) {
        if (t_state.local < t_P.global) {
            t_P.global = t_state.local;
        }
        return;
    }

    int i = 0;
    for (auto it = t_P.subsets.begin(); it != t_P.subsets.end(); ++it, ++i) {
        if (!t_state.usedKeys[i]) {
            for (const auto& extension : it->second) {

            }
        }
    }
}

