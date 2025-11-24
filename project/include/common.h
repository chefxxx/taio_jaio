//
// Created by Mateusz Mikiciuk on 18/11/2025.
//

#ifndef COMMON_H
#define COMMON_H

#include "eigen_port.h"

// https://cp-algorithms.com/combinatorics/binomial-coefficients.html
inline long choose(const long n, const long k)
{
    double res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * static_cast<double>(n - k + i) / i;
    }
    return static_cast<long>(res + 0.01);
}

inline long completeVerticesNumber(const long t_v1, long t_v2, const int t_k)
{
    while (choose(t_v2, t_v1) < t_k)
        t_v2++;
    return t_v2;
}

inline void extendVertices(Matrix &t_A, const long t_n)
{
    if (t_n == t_A.rows())
        return;
    const long beforeN = t_A.rows();
    t_A.conservativeResize(t_n, t_n);
    for (long i = beforeN; i < t_n; ++i) {
        t_A.row(i).setZero();
        t_A.col(i).setZero();
    }
}

inline bool checkIsomorphism(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    const auto A1prim = t_M * t_A2 * t_M.transpose();
    return (t_A1.array() <= A1prim.array()).all();
}

inline Matrix computeSubgraphFromMapping(const Matrix &t_A1, const Matrix &t_M) { return t_M.transpose() * t_A1 * t_M; }

inline Matrix computeExtension(const Matrix &t_A1, const Matrix &t_A2, const Matrix &t_M)
{
    auto A2prim = computeSubgraphFromMapping(t_A1, t_M);
    A2prim -= t_A2;
    A2prim = A2prim.cwiseMax(0);
    return A2prim;
}


#endif // COMMON_H
