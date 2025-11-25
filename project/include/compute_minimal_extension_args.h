//
// Created by Mateusz Mikiciuk on 24/11/2025.
//

#ifndef COMPUTE_MINIMAL_EXTENSION_ARGS_H
#define COMPUTE_MINIMAL_EXTENSION_ARGS_H

#include <__compare/ordering.h>
#include <unordered_set>

#include "eigen_port.h"
#include "mappings_key.h"

struct Extension
{
    explicit Extension(const Matrix &mtx)
        : graph(mtx)
    {
    }

    Matrix graph;

    std::strong_ordering operator<=> (const Extension &other) const
    {
        const long edgesCurrent = graph.sum();
        const long edgesOther   = other.graph.sum();
        if (edgesCurrent > edgesOther) {
            return std::strong_ordering::greater;
        }
        if (edgesCurrent < edgesOther) {
            return std::strong_ordering::less;
        }
        return std::strong_ordering::equal;
    }
};

/**
 *
 * @param t_local type of this variable is Extension, this is our base
 * @param t_extension type of this variable is Matrix, we extend base using this matrix
 * @return resulting extension
 */
inline Extension extendLocal(const Extension &t_local, const Matrix &t_extension)
{
    const auto &curr   = t_local.graph;
    const auto  result = curr.cwiseMax(t_extension).eval();
    return Extension{result};
}

inline std::vector<bool> generateNewKeys(const std::vector<bool> &t_oldKeys, const int t_idx)
{
    auto newKeys = t_oldKeys;
    newKeys[t_idx] = true;
    return newKeys;
}

struct ME_Problem
{
    ME_Problem(const Matrix &t_global, const std::unordered_map<BitVecKey, std::vector<Matrix>> &t_extensions) : global(t_global), subsets(t_extensions)
    Extension                                          global;
    std::unordered_map<BitVecKey, std::vector<Matrix>> subsets;
};

struct ME_State
{
    ME_State(const int t_numberOfExtensionsToFind, const Matrix &t_extension, const size_t t_subsetsNumber) : k(t_numberOfExtensionsToFind), local(t_extension)
    {
        usedKeys = std::vector(t_subsetsNumber, false);
    }

    ME_State(const std::vector<bool> &t_keys, const int t_numberOfExtensionsToFind, const Extension &t_extension)
        : k(t_numberOfExtensionsToFind)
        , usedKeys(t_keys)
        , local(t_extension)
    {
    }

    int               k;
    std::vector<bool> usedKeys;
    Extension         local;
};

#endif // COMPUTE_MINIMAL_EXTENSION_ARGS_H
