//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include "io_manager.h"

#include <exact_solution_infra.h>
#include <fstream>
#include <iostream>
#include <spdlog/spdlog.h>
#include <tuple>

#include "common.h"

std::tuple<Matrix, Matrix> parseInputFile(const std::string_view t_inputFileName)
{
    spdlog::info("Reading file: {}...", t_inputFileName);
    std::ifstream inputFile(t_inputFileName.data());
    if (!inputFile.is_open()) {
        spdlog::error("Failed to open file {}", t_inputFileName);
        exit(EXIT_FAILURE);
    }

    int lineNumber = 0;
    auto a1 = convertToMatrix(inputFile, lineNumber);
    auto a2 = convertToMatrix(inputFile, lineNumber);
    return std::make_tuple(a1, a2);
}

Matrix convertToMatrix(std::ifstream &inputFile, int& lineNumber)
{
    std::string line;
    std::getline(inputFile, line);
    ++lineNumber;
    try {
        const auto v = std::stoul(line);
        ++lineNumber;
        Matrix     a(v, v);

        for (unsigned i = 0; i < v; ++i, ++lineNumber) {
            std::getline(inputFile, line);
            std::stringstream values(line);
            std::string       segment;
            std::vector<int>  segList;
            while (std::getline(values, segment, ' ')) {
                segList.push_back(std::stoi(segment));
            }
            if (segList.size() != v) {
                spdlog::error("The number of elements is different than the declared one. The error occurred in line: {}", lineNumber);
                exit(EXIT_FAILURE);
            }
            for (unsigned j = 0; j < v; ++j) {
                a(i, j) = segList[j];
            }
        }
        return a;
    } catch (const std::exception &e) {
        spdlog::error("Failed to parse input file: {}. The error occurred in line: {}", e.what(), lineNumber);
        exit(EXIT_FAILURE);
    }
}

const std::string COLOR_YELLOW = "\033[93m";
const std::string COLOR_RESET = "\033[0m";
constexpr int WIDTH = 3;

void dualPrint(const std::string &text, std::ofstream *outputFile, const int width = 0, const bool colored = false)
{
    if (colored)
        std::cout << COLOR_YELLOW << std::setw(width) << text << COLOR_RESET;
    else
        std::cout << std::setw(width) << text;
    if (outputFile != nullptr)
        *outputFile << std::setw(width) << text;
}

void printMatricesAfterAlgorithm(const Matrix  &t_originalMatrix,
                                 const Matrix  &t_updatedMatrix,
                                 std::ofstream *t_outputFile)
{
    const int oldN = t_originalMatrix.rows();
    const int oldM = t_originalMatrix.cols();
    const int newN = t_updatedMatrix.rows();
    const int newM = t_updatedMatrix.cols();

    spdlog::info("Printing extensions result...");

    const int dist = computeDistance(t_originalMatrix, t_updatedMatrix);
    dualPrint("The distance between G2 and its extension: ", t_outputFile);
    dualPrint(fmt::format("{}", dist), t_outputFile, 0, true);
    dualPrint("\n", t_outputFile);

    dualPrint("\n=== ORIGINAL MATRIX FOR GRAPH G2 ===\n", t_outputFile);

    for (int i = 0; i < oldN; ++i, dualPrint("\n", t_outputFile)) {
        for (int j = 0; j < oldM; ++j) {
            const int cost = t_originalMatrix(i, j);
            dualPrint(std::to_string(cost), t_outputFile, WIDTH);
        }
    }

    dualPrint("\n=== EXTENDED MATRIX FOR GRAPH G2 ===\n", t_outputFile);

    for (int i = 0; i < newN; ++i, dualPrint("\n", t_outputFile)) {
        for (int j = 0; j < newM; ++j) {
            int cost = t_updatedMatrix(i, j);
            if (cost > t_originalMatrix(i, j)) {
                dualPrint(std::to_string(cost), t_outputFile, WIDTH, true);
            } else {
                dualPrint(std::to_string(cost), t_outputFile, WIDTH);
            }
        }
    }

    dualPrint("\n\n", t_outputFile);
}

void printMultipleMappings(const std::vector<Matrix> &t_mappings, const int t_number, std::ofstream *t_outputFile)
{
    spdlog::info("Printing exact mappings result...");
    dualPrint("\n", t_outputFile);
    for (int i = 0; i < t_number; ++i) {
        const auto map = getVectorOfMappingsFromMatrix(t_mappings[i]);
        dualPrint("[", t_outputFile);
        for (size_t k = 0; k < map.size(); ++k) {
            if (k < map.size() - 1)
                dualPrint(fmt::format("{}:{}, ", k, map[k]), t_outputFile);
            else
                dualPrint(fmt::format("{}:{}", k, map[k]), t_outputFile);
        }
        dualPrint("]\n", t_outputFile);
    }
    dualPrint("\n", t_outputFile);
}