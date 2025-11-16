//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <spdlog/spdlog.h>
#include <set>

#include "exact_solution_infra.h"

void performExactAlgorithm(const Matrix& A1, const Matrix& A2)
{
    spdlog::info("Preparing exact algorithm run...");
    // -----------------------
    // Prepare input variables
    // -----------------------
    const auto rows = A1.rows();
    const auto cols = A2.rows();
    Matrix M(rows, cols);
    M.setZero();
    const int R = 0;
    std::set<int> C;
}
