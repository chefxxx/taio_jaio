//
// Created by mshamrai on 12/2/25.
//

#ifndef TAIO_PROJECT_APPROXIMATIOIN_ALGORITHM_RUN_EFFICIENCY_H
#define TAIO_PROJECT_APPROXIMATIOIN_ALGORITHM_RUN_EFFICIENCY_H

#include "approximation_algorithm.h"

void runApproximationAlgorithmEfficiency(unsigned int numberOfTests = 10, unsigned int step = 10,
    unsigned int maxMult = 10);

void runApproximationWithFixedSizes(unsigned int numberOfTests = 10, unsigned int step = 10,
    unsigned int startM = 5, unsigned int maxMult = 10, unsigned int avarageOf = 5);

#endif // TAIO_PROJECT_APPROXIMATIOIN_ALGORITHM_RUN_EFFICIENCY_H
