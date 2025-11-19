//
// Created by mshamrai on 11/16/25.
//

#ifndef TAIO_PROJECT_GENERATE_START_COST_H
#define TAIO_PROJECT_GENERATE_START_COST_H

#include "eigen_port.h"

Matrix generateStartCost(const Matrix &m_1, const Matrix &m_2);

std::map<std::vector<int>, int> findLabels(const std::vector<std::vector<int>> &sources1, const std::vector<std::vector<int>> &sources2);
#endif // TAIO_PROJECT_GENERATE_START_COST_H
