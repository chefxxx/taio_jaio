//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#ifndef EIGEN_PORT_H
#define EIGEN_PORT_H

#include <Eigen/Dense>

typedef Eigen::Matrix<int, Eigen::Dynamic, Eigen::Dynamic> Matrix;

inline std::vector<int> getIndicesOfOutNeighbors(Matrix const& m, int vertexIndex)
{
    long n = m.rows();
    auto res = std::vector<int>();
    for (int i = 0; i < n; ++i) {
        if (m(vertexIndex, i) > 0)
            res.push_back(i);
    }
    return res;
}

inline std::vector<int> getIndicesOfInNeighbors(Matrix const& m, int vertexIndex)
{
    return getIndicesOfOutNeighbors(m.transpose(), vertexIndex);
}

inline std::vector<int> getNumberOfOutNeighbors(Matrix const& m)
{
    long n = m.rows();
    auto res = std::vector(n, 0);
    for (int i = 0; i < n; ++i) {
        res[i] = getIndicesOfOutNeighbors(m, i).size();
    }
    return res;
}

inline std::vector<int> getNumberOfInNeighbors(Matrix const& m)
{
    return getNumberOfOutNeighbors(m.transpose());
}

#endif // EIGEN_PORT_H
