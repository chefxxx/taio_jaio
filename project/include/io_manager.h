//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef IO_MANAGER_H
#define IO_MANAGER_H

#include <string_view>

#include "eigen_port.h"

std::tuple<Matrix, Matrix> parseInputFile(std::string_view t_inputFileName);
Matrix convertToMatrix(std::ifstream &inputFile);


#endif // IO_MANAGER_H
