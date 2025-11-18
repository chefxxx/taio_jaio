//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include "io_manager.h"

#include <fstream>
#include <spdlog/spdlog.h>
#include <tuple>

std::tuple<Matrix, Matrix> parseInputFile(const std::string_view t_inputFileName)
{
    spdlog::info("Reading file: {}...", t_inputFileName);
    std::ifstream inputFile(t_inputFileName.data());
    if (!inputFile.is_open()) {
        spdlog::error("Failed to open file {}", t_inputFileName);
        exit(EXIT_FAILURE);
    }

    auto a1 = convertToMatrix(inputFile);
    auto a2 = convertToMatrix(inputFile);
    return std::make_tuple(a1, a2);
}

Matrix convertToMatrix(std::ifstream &inputFile)
{
    std::string line;
    std::getline(inputFile, line);
    const auto v = std::stoi(line);
    Matrix     a(v, v);

    for (int i = 0; i < v; ++i) {
        std::getline(inputFile, line);
        std::stringstream values(line);
        std::string       segment;
        std::vector<int>  segList;
        while (std::getline(values, segment, ' ')) {
            segList.push_back(std::stoi(segment));
        }
        for (int j = 0; j < v; ++j) {
            a(i, j) = segList[j];
        }
    }
    return a;
}