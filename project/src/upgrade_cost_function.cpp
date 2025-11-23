//
// Created by mshamrai on 11/23/25.
//
#include "upgrade_cost_function.h"

void changeCostForOneVertex(int v, const std::vector<int> &mapping, const std::vector<std::vector<int>> &neighbors_1,
    const std::vector<std::vector<int>> &neighbors_2, std::vector<double> &costRef, const Eigen::MatrixXd &costMatrix)
{
    int n = neighbors_1[v].size();
    int mapped = mapping[v];
    for (int i = 0; i < n; i++) {
        int neighbor = neighbors_1[v][i];
        int mappedNeighbor = mapping[neighbor];
        std::ranges::find(neighbors_2[mapped], mappedNeighbor) != neighbors_2[mapped].end() ?
            costRef[v] -= costMatrix(v, mapped) : costRef[v] += costMatrix(v, mapped);
    }
}

Eigen::MatrixXd upgradeCostFunction(const Eigen::MatrixXd &costMatrix, const std::vector<int> &mapping,
    const Matrix &m_1, const Matrix &m_2)
{
    Eigen::MatrixXd res = Eigen::MatrixXd::Zero(costMatrix.rows(), costMatrix.cols());
    for (int i = 0; i < res.rows(); ++i) {
        for (int j = 0; j < res.cols(); ++j) {
            res(i, j) = costMatrix(i, j);
        }
    }
    int n = m_1.rows(); // The number of vertices in G1
    std::vector<std::vector<int>> outNeighbors_1 = fillNeighborsStructure(m_1, getIndicesOfOutNeighbors);
    std::vector<std::vector<int>> inNeighbors_1 = fillNeighborsStructure(m_1, getIndicesOfInNeighbors);
    std::vector<std::vector<int>> outNeighbors_2 = fillNeighborsStructure(m_2, getIndicesOfOutNeighbors);
    std::vector<std::vector<int>> inNeighbors_2 = fillNeighborsStructure(m_2, getIndicesOfInNeighbors);

    std::vector<double> changesSumIn(n, 0);
    std::vector<double> changesSumOut(n, 0);
    for (int i = 0; i < n; ++i) {
        if (!inNeighbors_1[i].empty()) {
            changeCostForOneVertex(i, mapping, inNeighbors_1, inNeighbors_2, changesSumIn, res);
            double add = (changesSumIn[i] / (inNeighbors_1[i].size() * 2)) ;
            res(i, mapping[i]) += add;
        }
        if (!outNeighbors_1[i].empty()) {
            changeCostForOneVertex(i, mapping, outNeighbors_1, outNeighbors_2, changesSumOut, res);
            res(i , mapping[i]) += (changesSumOut[i] / (outNeighbors_1[i].size() * 2));
        }
    }
    return res;
}