//
// Created by mshamrai on 11/23/25.
//

#ifndef TAIO_PROJECT_UPGRADE_COST_FUNCTION_H
#define TAIO_PROJECT_UPGRADE_COST_FUNCTION_H

#include "eigen_port.h"

void changeCostForOneVertex(int v, const std::vector<int> &mapping, const std::vector<std::vector<int>> &neighbors_1,
    const std::vector<std::vector<int>> &neighbors_2, std::vector<int> &costRef, const Eigen::MatrixXd &costMatrix);

Eigen::MatrixXd upgradeCostFunction(const Eigen::MatrixXd &costMatrix, const std::vector<int> &mapping,
    const Matrix &m_1, const Matrix &m_2);

#endif // TAIO_PROJECT_UPGRADE_COST_FUNCTION_H
