//
// Created by Mateusz Mikiciuk on 24/11/2025.
//

#ifndef COMPUTE_MINIMAL_EXTENSION_ARGS_H
#define COMPUTE_MINIMAL_EXTENSION_ARGS_H

#include <__compare/ordering.h>
#include <unordered_set>

#include "mappings_key.h"
#include "eigen_port.h"

struct Extension
{
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

struct ME_Problem
{
    Extension global;
    std::unordered_map<BitVecKey, std::vector<Matrix>> subsets;
};

struct ME_State
{
    ME_State(const std::vector<bool> &t_keys, const int t_numberOfExtensionsToFind, const Extension &t_extension)
    :     numberOfExtensionsToFind(t_numberOfExtensionsToFind)
        , usedKeys(t_keys)
        , local(t_extension)
    {}
    int               numberOfExtensionsToFind;
    std::vector<bool> usedKeys;
    Extension         local;
};

#endif // COMPUTE_MINIMAL_EXTENSION_ARGS_H
