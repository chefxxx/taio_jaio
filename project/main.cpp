#include <iostream>
#include <spdlog/spdlog.h>

#include "approximation_algorithm.h"
#include "exact_solution_infra.h"
#include "io_manager.h"
#include "options_reader.h"

__attribute__((noreturn)) void Usage()
{
    std::cerr << "USAGE: ./pname [-input-file </path/to/input_file.txt>] [-k=1 <number of subgraph(s) to find>] " <<
                 "[-output-file </path/to/output_file.txt>] [-type=exact exact/approximation]";
    exit(EXIT_FAILURE);
}

int main(const int argc, const char **argv)
{
    std::string inputFileName = "";
    std::string outputFileName = "";
    std::string algorithm = "";
    int k = -1;


    // ---------------
    // Read input args
    // ---------------
    try {
        getAllParameters(inputFileName, outputFileName, algorithm, k, argc, argv);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        Usage();
    }

    // -----------
    // Parse input
    // -----------
    const auto [A1, A2] = parseInputFile(inputFileName);

    // -------------
    // Run algorithm
    // -------------
    if (algorithm == "exact") {
        spdlog::info("Exact solution algorithm is called...");
        performExactAlgorithm(A1, A2, k);
    }
    else if (algorithm == "approximation") {
        spdlog::info("Approximation solution algorithm is called...");
        approximationAlgorithm(A1, A2);
    }
    return 0;
}
