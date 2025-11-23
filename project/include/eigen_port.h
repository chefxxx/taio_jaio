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


inline Matrix addZeroColumnAndZeroRowToMatrix(const Matrix &m)
{
    int oldN = m.rows();
    int oldM = m.cols();
    Matrix res(oldN + 1, oldM + 1);
    for (int j = 0; j < oldM + 1; ++j)
        res(0, j) = 0;
    for (int i = 1; i < oldN + 1; ++i) {
        res(i, 0) = 0;
        for (int j = 1; j < oldM + 1; ++j) {
            res(i, j) = m(i - 1, j - 1);
        }
    }
    return res;
}

inline std::vector<std::vector<int>> fillNeighborsStructure(const Matrix &m,
    const std::function<std::vector<int>(Matrix, int)> &f)
{
    auto s = m.rows();
    std::vector<std::vector<int>> res = std::vector<std::vector<int>>(s);
    for (int i = 0; i < s; ++i) {
        res[i] = f(m, i);
    }
    return res;
}

inline std::vector<int> getVectorOfMappingsFromMatrix(const Matrix &mapping)
{
    int n = mapping.rows();
    int m = mapping.cols();
    std::vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mapping(i, j) == 1)
                res[i] = j;
        }
    }
    return res;
}
#endif // EIGEN_PORT_H
