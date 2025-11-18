#include <iostream>
#include <spdlog/spdlog.h>

#include "io_manager.h"
#include "exact_solution_infra.h"

__attribute__((noreturn)) void Usage()
{
    std::cerr << "USAGE: ./pname [file_name=</path/to/input_file.txt>] [k=<number of subgraph(s) to find>]";
    exit(EXIT_FAILURE);
}

int main(const int argc, const char **argv)
{
    // ---------------
    // Read input args
    // ---------------
    if (argc != 3) {
        Usage();
    }
    const std::string fileName = argv[1];
    const int k = std::stoi(argv[2]);

    // -----------
    // Parse input
    // -----------
    const auto [A1, A2] = parseInputFile(fileName);

    // -------------
    // Run exact alg
    // -------------
    performExactAlgorithm(A1, A2, k);

    return 0;
}
