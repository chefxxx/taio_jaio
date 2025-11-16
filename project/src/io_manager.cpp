//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <fstream>
#include <spdlog/spdlog.h>
#include "io_manager.h"

void parseInputFile(const std::string_view t_inputFileName)
{
    const std::ifstream inputFile(t_inputFileName);
    if (!inputFile.is_open()) {
        spdlog::error("Failed to open file {}", t_inputFileName);
        exit(EXIT_FAILURE);
    }

    const std::string line;

}