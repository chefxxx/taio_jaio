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
        auto graphs = generateTwoGraphs(step, step, maxMult, 1111);
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