//
// Created by mshamrai on 12/2/25.
//

#include <gtest/gtest.h>

#include "approximatioin_algorithm_run_efficiency.h"

TEST(ApproximationAlgorithmEfficiencyTest, step10TestMaxMult10)
{
    unsigned int numberOfSteps = 30;
    unsigned int step = 10;
    unsigned int maxMult = 10;
    runApproximationAlgorithmEfficiency(numberOfSteps, step, maxMult);
};
