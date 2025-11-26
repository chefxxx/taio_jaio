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

void printMatricesAfterAlgorithm(const Matrix &originalMatrix, const Matrix &updatedMatrix)
{
    static const std::string COLOR_YELLOW = "\033[93m";
    static const std::string COLOR_RESET = "\033[0m";
    const int oldN = originalMatrix.rows();
    const int oldM = originalMatrix.cols();
    const int newN = updatedMatrix.rows();
    const int newM = updatedMatrix.cols();

    std::cout << "\n\n=== ORIGINAL MATRIX FOR GRAPH G2 ===\n\n";
    for (int i = 0; i < oldN; ++i, std::cout << "\n") {
        for (int j = 0; j < oldM; ++j) {
            const int cost = originalMatrix(i, j);
            std::cout << std::setw(3) << cost;
        }
    }

    std::cout << "\n\n=== EXTENDED MATRIX FOR GRAPH G2 ===\n\n";
    for (int i = 0; i < newN; ++i, std::cout << "\n") {
        for (int j = 0; j < newM; ++j) {
            const int cost = updatedMatrix(i, j);
            if (cost > originalMatrix(i, j)) {
                std::cout << COLOR_YELLOW << std::setw(3) << cost << COLOR_RESET;
            } else {
                std::cout << std::setw(3) << cost;
            }
        }
    }

    std::cout << "\n\n";
}