//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include "io_manager.h"

#include <fstream>
#include <iostream>
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

void printMatricesAfterAlgorithm(const Matrix &originalMatrix, const Matrix &updatedMatrix, std::ofstream* outputFile)
{
    static const std::string COLOR_YELLOW = "\033[93m";
    static const std::string COLOR_RESET = "\033[0m";
    static const int WIDTH = 3;
    int oldN = originalMatrix.rows();
    int oldM = originalMatrix.cols();

    int newN = updatedMatrix.rows();
    int newM = updatedMatrix.cols();

    auto dualPrint = [&](std::string text, int width = 0, bool colored = false) {
        if (colored)
            std::cout << COLOR_YELLOW << std::setw(width) << text << COLOR_RESET;
        else
            std::cout << std::setw(width) << text;
        if (outputFile != nullptr)
            *outputFile << std::setw(width) << text;
    };

    dualPrint("=== ORIGINAL MATRIX FOR GRAPH G2 ===");
    dualPrint("\n\n");

    for (int i = 0; i < oldN; ++i, dualPrint("\n")) {
        for (int j = 0; j < oldM; ++j) {
            int cost = originalMatrix(i, j);
            dualPrint(std::to_string(cost), WIDTH);
        }
    }

    dualPrint("\n\n");
    dualPrint("=== EXTENDED MATRIX FOR GRAPH G2 ===");
    dualPrint("\n\n");

    for (int i = 0; i < newN; ++i, dualPrint("\n")) {
        for (int j = 0; j < newM; ++j) {
            int cost = updatedMatrix(i, j);
            if (cost > originalMatrix(i, j)) {
                dualPrint(std::to_string(cost), WIDTH, true);
            } else {
                dualPrint(std::to_string(cost), WIDTH);
            }
        }
    }

    dualPrint("\n\n");
}