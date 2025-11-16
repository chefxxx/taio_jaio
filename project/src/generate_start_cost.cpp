//
// Created by mshamrai on 11/16/25.
//
#include "generate_start_cost.h"

using Eigen::MatrixXd;

MatrixXd generateStartCost(const MatrixXd &m_1, const MatrixXd &m_2)
{
    constexpr short SIZE_OF_FIRST_SOURCE = 2;
    // Define the sizes for matrices
    int s1 = m_1.rows();
    int s2 = m_2.rows();
    std::vector labels_1(s1, -1);
    std::vector labels_2(s2, -1);

    std::vector sources_1(s1, std::vector(SIZE_OF_FIRST_SOURCE, 0));
    std::vector sources_2(s2, std::vector(SIZE_OF_FIRST_SOURCE, 0));

    return MatrixXd::Identity(s1, s1);
}