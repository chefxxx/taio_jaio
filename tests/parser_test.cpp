//
// Created by Mateusz Mikiciuk on 16/11/2025.
//

#include <gtest/gtest.h>

#include "io_manager.h"

// TEST(ParserTest, smallMatricesReadoutSuite)
// {
//     const std::string        fileName = "../../sample_files/small_graphs_test.txt";
//     Eigen::Matrix<int, 6, 6> first{
//         {1, 2, 3, 4, 5, 6},
//         {6, 5, 4, 3, 2, 1},
//         {1, 2, 3, 4, 5, 6},
//         {6, 5, 4, 3, 2, 1},
//         {1, 2, 3, 4, 5, 6},
//         {6, 5, 4, 3, 2, 1},
//     };
//     Eigen::Matrix<int, 4, 4> second{{4, 4, 4, 4}, {4, 4, 4, 4}, {4, 4, 4, 4}, {4, 4, 4, 4}};
//     const auto [M1, M2] = parseInputFile(fileName);
//     ASSERT_EQ(M1.rows(), 6);
//     ASSERT_EQ(M1.cols(), 6);
//     ASSERT_EQ(M2.rows(), 4);
//     ASSERT_EQ(M2.cols(), 4);
//     for (int i = 0; i < M1.rows(); ++i) {
//         for (int j = 0; j < M1.cols(); ++j) {
//             ASSERT_EQ(first(i, j), M1(i, j));
//         }
//     }
//     for (int i = 0; i < M2.rows(); ++i) {
//         for (int j = 0; j < M2.cols(); ++j) {
//             ASSERT_EQ(second(i, j), M2(i, j));
//         }
//     }
// }