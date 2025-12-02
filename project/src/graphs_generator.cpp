//
// Created by mshamrai on 12/1/25.
//
#include "graphs_generator.h"

#include <random>

auto generateTwoGraphs(unsigned int M, unsigned int N, unsigned int maxMult, unsigned int seed)
    -> std::pair<Matrix, Matrix>
{
    std::mt19937 rng(seed);

    std::uniform_int_distribution<unsigned> distMult(0, maxMult);

    Matrix G1 = Matrix::Zero(N, N);
    Matrix G2 = Matrix::Zero(M, M);

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            G1(i, j) = distMult(rng);

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            G2(i, j) = distMult(rng);

    return std::make_pair(G1, G2);
}

std::pair<Matrix, Matrix> generateTwoGraphs(unsigned int minM, unsigned int maxM, unsigned int maxMult)
{
    std::random_device rd;
    unsigned int seed = rd();
    return generateTwoGraphs(minM, maxM, maxMult, seed);
}