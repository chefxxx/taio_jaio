//
// Created by mshamrai on 11/25/25.
//
#include "options_reader.h"
#include <spdlog/spdlog.h>

const std::string EXACT_TYPE = "exact";
const std::string APPROX_TYPE = "approximation";
const std::string DEFAULT_OUTPUT_FILE = "result";

void getAllParameters(std::string &inFile, std::string &outFile, std::string &algType, int& k, int argc, const char **argv)
{
    static int defaultK = 1;
    algType = EXACT_TYPE;
    k = defaultK;
    outFile = DEFAULT_OUTPUT_FILE;
    // Which algorithm is called
    if (cmdOptionExists(argv, argv + argc, "-type"))
    {
        const char* optionString = getCmdOption(argv, argv + argc, "-type");
        std::string type = optionString;
        std::ranges::transform(type, type.begin(), ::tolower);
        if (type == APPROX_TYPE) {
            algType = APPROX_TYPE;
        }
        else if (type != EXACT_TYPE) {
            spdlog::warn("Wrong option type: '{}'. The default option - '{}' algorithm is called", type, algType);
        }
    }
    spdlog::info("The {} type of algorithm is set", algType);

    // Path to the input file
    if (cmdOptionExists(argv, argv + argc, "-input-file")) {
        const char* optionString = getCmdOption(argv, argv + argc, "-input-file");
        inFile = optionString;
    } else {
        throw std::invalid_argument("Missing required option -input-file");
    }

    // Path to the output file
    if (cmdOptionExists(argv, argv + argc, "-output-file")) {
        const char* optionString = getCmdOption(argv, argv + argc, "-output-file");
        outFile = optionString;
    } else {
        spdlog::info("Default file name for the output file is set: {}", outFile);
    }

    // The number for the k
    if (cmdOptionExists(argv, argv + argc, "-k")) {
        const char* optionString = getCmdOption(argv, argv + argc, "-k");
        if (auto tmp = std::stoi(optionString, nullptr, 10); tmp <= 0) {
            spdlog::warn("Invalid k value: {}. The default one: {} is set", tmp, k);
        }
        else {
            k = tmp;
        }
    }
    else {
        spdlog::info("Default k value is set: {}", k);
    }
}