//
// Created by mshamrai on 12/2/25.
//

#include "approximatioin_algorithm_run_efficiency.h"

#include <spdlog/spdlog.h>

#include "approximation_algorithm.h"
#include "common.h"
#include "graphs_generator.h"


void runApproximationAlgorithmEfficiency(unsigned int numberOfTests, unsigned int step, unsigned int maxMult)
{
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    //std::string fileName;
    unsigned int tmp = step;
    for (unsigned i = 0; i < numberOfTests; ++i, step += tmp) {
        auto graphs = generateTwoGraphs(step, step, maxMult);
        Matrix G1 = graphs.first;
        Matrix G2 = graphs.second;

        //std::ofstream file(fileName);
        begin = std::chrono::steady_clock::now();
        auto updatedMapping = approximationAlgorithm(G1, G2);
        end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration<double, std::milli>(end - begin).count();
            spdlog::info("Czas: {:.3f} ms", duration);
    }
}

void runApproximationWithFixedSizes(unsigned int numberOfTests, unsigned int step,
    unsigned int startM, unsigned int maxMult, unsigned int avarageOf)
{
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    double cummulatedTime = 0.0;
    for (unsigned i = 0; i < numberOfTests; ++i, startM += step) {
        int tmpAverageOf = 0;
        for (unsigned int k = 1; k <= startM; k <<= 2) {
            for (unsigned j = 0; j < avarageOf; ++j, ++tmpAverageOf) {
                auto graphs = generateTwoGraphsWithGivenSizes(k, startM, maxMult);
                Matrix G1 = graphs.first;
                Matrix G2 = graphs.second;

                begin = std::chrono::steady_clock::now();
                auto updatedMapping = approximationAlgorithm(G1, G2);
                end = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration<double, std::milli>(end - begin).count();
                cummulatedTime += duration;
            }
        }
        spdlog::info("Czas {}: {:.3f} ms", startM, cummulatedTime / tmpAverageOf);
    }
}
