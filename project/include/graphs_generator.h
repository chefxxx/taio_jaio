//
// Created by mshamrai on 12/1/25.
//

#ifndef TAIO_PROJECT_GRAPHS_GENERATOR_H
#define TAIO_PROJECT_GRAPHS_GENERATOR_H

#include "eigen_port.h"

std::pair<Matrix, Matrix> generateTwoGraphs(unsigned int minM, unsigned int maxM, unsigned int maxMult,
    unsigned int seed);

std::pair<Matrix, Matrix> generateTwoGraphs(unsigned int minM, unsigned int maxM, unsigned int maxMult);

#endif // TAIO_PROJECT_GRAPHS_GENERATOR_H
