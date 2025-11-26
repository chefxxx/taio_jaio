//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <spdlog/spdlog.h>

#include "exact_solution_infra.h"
#include "io_manager.h"
#include "common.h"

constexpr int MAX_MULTIPLICITY = 256;
constexpr int MIN_MULTIPLICITY = -1;

void performExactAlgorithm(const Matrix &t_A1, const Matrix &t_A2, const long t_k)
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

    auto [SI_globalState, SI_initState, mappings, extensions] = prepareArgs_For_SubgraphIsomorphism(t_A1, t_A2);

    // ------------------
    // Run main algorithm
    // ------------------
    spdlog::info("Procedure SubgraphIsomorphismSerial run...");
    subgraphIsomorphismSerial(SI_globalState, SI_initState, mappings, extensions);
    spdlog::info("Procedure SubgraphIsomorphismSerial finished...");

    // -----------------------------------------
    // Return mappings when extension not needed
    // -----------------------------------------
    const auto [maps, graphs] = convertMappingsToResult(mappings);
    if (mappings.size() >= static_cast<size_t>(t_k)) {
        printMultipleMappings(maps, t_k);
        //TODO: save to file
        return;
    }

    // ------------------------------------------------------
    // Clear extensions where mapping exists and prepare args
    // ------------------------------------------------------
    clearExtensionsSubsetsWhereMappingExists(mappings, extensions);
    auto [ME_globalState, ME_initState] = prepareArgs_For_MinimalExtension(A2.rows(), mappings, extensions, t_k);

    // ----------------------
    // Find minimal extension
    // ----------------------
    spdlog::info("Procedure computeMinimalExtensionSerial run...");
    computeMinimalExtensionSerial(ME_globalState, ME_initState);
    spdlog::info("Procedure computeMinimalExtensionSerial finished...");

    // ----------------------
    // Return combined result
    // ----------------------
    printMultipleMappings(maps, maps.size());
    printMatricesAfterAlgorithm(A2, ME_globalState.global.matrix);
    // TODO: save to file
}

void subgraphIsomorphismSerial(const SI_Problem                                   &t_P,
                               SI_State                                           &t_state,
                               std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                               std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions)
{
    if (t_state.R == t_P.v1) {
        const auto key = BitVecKey(t_state.M);
        if ([[maybe_unused]] const auto isValid = checkIsomorphism(t_P.A1, t_P.A2, t_state.M)) {
            t_mappings.try_emplace(key, computeSubgraphFromMapping(t_P.A1, t_state.M));
        }
        else {
            if (!t_extensions.contains(key)) {
                t_extensions[key] = {};
            }
            t_extensions[key].push_back(computeExtension(t_P.A1, t_P.A2, t_state.M));
        }
        return;
    }

    for (size_t i = 0; i < t_state.cols.size(); ++i) {
        if (!t_state.cols[i]) {
            t_state.serialNextState(i);
            subgraphIsomorphismSerial(t_P, t_state, t_mappings, t_extensions);
            t_state.serialPrevState(i);
        }
    }
}

std::tuple<std::vector<Matrix>, std::vector<Matrix>>
convertMappingsToResult(const std::unordered_map<BitVecKey, Matrix> &t_mappings)
{
    std::vector<Matrix> maps;
    std::vector<Matrix> graphs;
    for (const auto &[key, subgraph] : t_mappings) {
        maps.push_back(key.M);
        graphs.push_back(subgraph);
    }
    return std::make_tuple(maps, graphs);
}

int computeDistance(const Matrix &t_M1, const Matrix &t_M2)
{
    // we count distance from t_M2
    const int sum1 = t_M1.sum();
    const int sum2 = t_M2.sum();
    return sum2 - sum1;
}

void clearExtensionsSubsetsWhereMappingExists(const std::unordered_map<BitVecKey, Matrix>        &t_mappings,
                                              std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions)
{
    // ReSharper disable once CppUseElementsView
    for (const auto &[key, matrix] : t_mappings) { // for all subsets that have mappings
        if (t_extensions.contains(key)) {
            t_extensions.erase(key);
        }
    }
}

void computeMinimalExtensionSerial(ME_Problem &t_P, ME_State t_state)
{
    if (t_state.k == 0) {
        if (t_state.local < t_P.global) {
            t_P.global = t_state.local;
        }
        return;
    }

    int i = 0;
    for (auto it = t_P.subsets.begin(); it != t_P.subsets.end(); ++it, ++i) {
        if (!t_state.usedKeys[i]) {
            const auto newKeys = generateNewKeys(t_state.usedKeys, i);
            for (const auto &extension : it->second) {
                // ReSharper disable once CppTooWideScopeInitStatement
                const auto nextLocal = extendLocal(t_state.local, extension);
                if (nextLocal < t_P.global) {
                    const ME_State next{newKeys, t_state.k - 1, nextLocal};
                    computeMinimalExtensionSerial(t_P, next);
                }
            }
        }
    }
}

std::tuple<ME_Problem, ME_State>
prepareArgs_For_MinimalExtension(const size_t                                              t_matrixSize,
                                 const std::unordered_map<BitVecKey, Matrix>              &t_mappings,
                                 const std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions,
                                 const long                                                t_k)
{
    const size_t k = t_k - t_mappings.size();
    Matrix       globMax{t_matrixSize, t_matrixSize};
    globMax.setConstant(MAX_MULTIPLICITY);
    Matrix localStarting{t_matrixSize, t_matrixSize};
    localStarting.setConstant(MIN_MULTIPLICITY);
    const ME_State   starting{k, localStarting, t_extensions.size()};
    const ME_Problem global{globMax, t_extensions};

    return std::make_tuple(global, starting);
}

std::tuple<SI_Problem,
           SI_State,
           std::unordered_map<BitVecKey, Matrix>,
           std::unordered_map<BitVecKey, std::vector<Matrix>>>
prepareArgs_For_SubgraphIsomorphism(const Matrix &t_A1, const Matrix &t_A2)
{
    assert(t_A1.rows() == t_A1.cols());
    assert(t_A2.rows() == t_A2.cols());
    Matrix M(t_A1.rows(), t_A2.rows());
    M.setZero();
    const std::vector<bool>                                  cols(M.cols());
    const SI_Problem                                         globalState{t_A1, t_A2};
    const SI_State                                           initState{cols, M, 0};
    const std::unordered_map<BitVecKey, Matrix>              mappings;
    const std::unordered_map<BitVecKey, std::vector<Matrix>> extensions;
    return std::make_tuple(globalState, initState, mappings, extensions);
}
