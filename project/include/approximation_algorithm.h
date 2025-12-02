//
// Created by mshamrai on 11/23/25.
//

#ifndef TAIO_PROJECT_APPROXIMATION_ALGORITHM_H
#define TAIO_PROJECT_APPROXIMATION_ALGORITHM_H

#include "eigen_port.h"

void printApproximationAlgorithmResult(const Matrix &graph_1, const Matrix &graph_2, const Matrix &updatedMapping,
    std::ofstream *outputFile);
Matrix approximationAlgorithm(const Matrix &graph_1, const Matrix &graph_2);

#endif // TAIO_PROJECT_APPROXIMATION_ALGORITHM_H
