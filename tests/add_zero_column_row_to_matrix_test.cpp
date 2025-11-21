//
// Created by mshamrai on 11/21/25.
//
#include <gtest/gtest.h>
#include "generate_start_cost.h"

class AddZeroColumnAndZeroRowToMatrix : public ::testing::Test
{
public:
    Matrix A1 = Matrix{{1, 2, 3, 4, 1},
                            {1, 2, 5, 3, 2},
                            {5, 5, 1, 2, -3},
                            {1, 1, 1, 1, -1}};
    Matrix A2 = Matrix{};
};

TEST_F(AddZeroColumnAndZeroRowToMatrix, add_column_and_row_to_normal_matrix)
{
    auto test_matrix = addZeroColumnAndZeroRowToMatrix(A1);

    Matrix exact_result = Matrix{{0, 0, 0, 0, 0, 0},
                                    {0, 1, 2, 3, 4, 1},
                                    {0, 1, 2, 5, 3, 2},
                                    {0, 5, 5, 1, 2, -3},
                                    {0, 1, 1, 1, 1, -1}};

    for (int i = 0; i < exact_result.rows(); ++i)
        for (int j = 0; j < exact_result.cols(); ++j)
            ASSERT_EQ(exact_result(i, j), test_matrix(i, j));
}

TEST_F(AddZeroColumnAndZeroRowToMatrix, add_column_and_row_to_empty_matrix)
{
    auto test_matrix = addZeroColumnAndZeroRowToMatrix(A2);

    Matrix exact_result = Matrix{{0}};

    for (int i = 0; i < exact_result.rows(); ++i)
        for (int j = 0; j < exact_result.cols(); ++j)
            ASSERT_EQ(exact_result(i, j), test_matrix(i, j));
}