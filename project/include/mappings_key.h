//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#ifndef MAPPINGS_KEY_H
#define MAPPINGS_KEY_H

#include <vector>

#include "eigen_port.h"

struct MappingsKey
{
    explicit MappingsKey(const Matrix &t_matrix)
    {
        m_verticesUsed = std::vector(t_matrix.rows(), false);
        for (int i = 0; i < t_matrix.rows(); ++i) {
            const auto row = t_matrix.row(i);
            for (int j = 0; j < t_matrix.cols(); ++j) {
                if (row[j] == 1) {
                    m_verticesUsed[i] = true;
                    break;
                }
            }
        }
    }

    std::vector<bool> verticesUsed;
};

inline void hash_combine(size_t &seed, const size_t value)
{
    seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

template<>
struct std::hash<MappingsKey>
{
    size_t operator()(const MappingsKey &t_key) const noexcept
    {
        size_t hash = 0;
        for (const bool b : t_key.verticesUsed) {
            hash_combine(hash, b ? 1 : 0);
        }
        return hash;
    }
};


#endif //MAPPINGS_KEY_H
