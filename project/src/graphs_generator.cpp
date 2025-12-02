//
// Created by mshamrai on 12/1/25.
//
#include "graphs_generator.h"

#include <random>

std::pair<Matrix, Matrix> generateTwoGraphs(unsigned int minM, unsigned int maxM, unsigned int maxMult,
    unsigned int seed)
{
    std::mt19937 rng(seed);
    std::uniform_int_distribution distSize(minM, maxM);
    std::uniform_int_distribution<unsigned> distMult(0, maxMult);

    int m = distSize(rng);
    distSize = std::uniform_int_distribution<unsigned>(minM, m);
    int n = distSize(rng);

    Matrix G1 = Matrix::Zero(n, n);
    Matrix G2 = Matrix::Zero(m, m);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            G1(i, j) = distMult(rng);

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < m; ++j)
            G2(i, j) = distMult(rng);

    return std::make_pair(G1, G2);
}

std::pair<Matrix, Matrix> generateTwoGraphs(unsigned int minM, unsigned int maxM, unsigned int maxMult)
{
    std::random_device rd;
    unsigned int seed = rd();
    return generateTwoGraphs(minM, maxM, maxMult, seed);
}

std::pair<Matrix, Matrix> generateTwoGraphsWithGivenSizes(unsigned int N, unsigned int M, unsigned int maxMult,
    unsigned int seed)
{
    std::mt19937 rng(seed);
    std::uniform_int_distribution<unsigned> distMult(0, maxMult);
    Matrix G1 = Matrix::Zero(N, N);
    Matrix G2 = Matrix::Zero(M, M);

    for (unsigned i = 0; i < N; ++i)
        for (unsigned j = 0; j < N; ++j)
            G1(i, j) = distMult(rng);

    for (unsigned i = 0; i < M; ++i)
        for (unsigned j = 0; j < M; ++j)
            G2(i, j) = distMult(rng);

    return std::make_pair(G1, G2);
}

std::pair<Matrix, Matrix> generateTwoGraphsWithGivenSizes(unsigned int N, unsigned int M, unsigned int maxMult)
{
    std::random_device rd;
    unsigned int seed = rd();
    return generateTwoGraphsWithGivenSizes(N, M, maxMult, seed);
}