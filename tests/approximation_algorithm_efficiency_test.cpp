//
// Created by mshamrai on 12/2/25.
//

#include <gtest/gtest.h>

#include "approximatioin_algorithm_run_efficiency.h"
#include "spdlog/fmt/bundled/chrono.h"

TEST(ApproximationAlgorithmEfficiencyTest, step10TestMaxMult10)
{
    unsigned int numberOfSteps = 20;
    unsigned int step = 10;
    unsigned int maxMult = 25;
    runApproximationAlgorithmEfficiency(numberOfSteps, step, maxMult);
};

TEST(ApproximationAlgorithmEfficiencyTest, step10TestMaxMult10WithEverySizeOfSubgraph)
{
    unsigned int numberOfSteps = 20;
    unsigned int step = 10;
    unsigned int maxMult = 25;
    unsigned int avarageOf = 5;
    runApproximationWithFixedSizes(numberOfSteps, step, step, maxMult, avarageOf);
}
