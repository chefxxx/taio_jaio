//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#ifndef MAPPINGS_KEY_H
#define MAPPINGS_KEY_H

#include <vector>

#include "eigen_port.h"

struct MappingsKey
{
    explicit MappingsKey(const Matrix &t_matrix)
    {
        m_verticesUsed = std::vector(t_matrix.rows(), false);
        for (int i = 0; i < t_matrix.rows(); ++i) {
            const auto row = t_matrix.row(i);
            for (int j = 0; j < t_matrix.cols(); ++j) {
                if (row[j] == 1) {
                    m_verticesUsed[i] = true;
                    break;
                }
            }
        }
    }

private:
    std::vector<bool> m_verticesUsed;
};

#endif //MAPPINGS_KEY_H
