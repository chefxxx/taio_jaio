//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <string_view>

#include "eigen_port.h"

std::tuple<Matrix, Matrix> parseInputFile(std::string_view t_inputFileName);
Matrix                     convertToMatrix(std::ifstream &inputFile, int& lineNumber);

void printMatricesAfterAlgorithm(const Matrix  &t_originalMatrix,
                                 const Matrix  &t_updatedMatrix,
                                 std::ofstream *t_outputFile = nullptr);
void printMultipleMappings(const std::vector<Matrix> &t_mappings, int t_number, std::ofstream *t_outputFile);

#endif // IO_MANAGER_H
