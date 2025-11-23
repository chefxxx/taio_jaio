//
// Created by Mateusz Mikiciuk on 19/11/2025.

#ifndef MAPPINGS_KEY_H
#define MAPPINGS_KEY_H

#include <vector>

#include "eigen_port.h"

struct BitVecKey
{
    explicit BitVecKey(const Matrix &t_matrix) : M(t_matrix)
    {
        bits = std::vector(t_matrix.cols(), false);
        for (int j = 0; j < t_matrix.cols(); ++j) {
            bits[j] = (t_matrix.col(j).array() == 1).any();
        }
    }

    bool operator==(const BitVecKey &other) const { return bits == other.bits; }

    std::vector<bool> bits;
    Matrix M;
};

inline void hash_combine(size_t &seed, const size_t value)
{
    seed ^= value + 0x9e3779b97f4a7c15ULL + (seed << 6) + (seed >> 2);
}

template <> struct std::hash<BitVecKey>
{
    size_t operator()(const BitVecKey &t_key) const noexcept
    {
        size_t hashValue = 0;
        for (const bool b : t_key.bits) {
            hash_combine(hashValue, b ? 1 : 0);
        }
        return hashValue;
    }
};


#endif // MAPPINGS_KEY_H
