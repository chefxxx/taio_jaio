//
// Created by mshamrai on 11/21/25.
//
#include "eigen_port.h"
#include "gtest/gtest.h"
#include "hungarian_method.h"

class HungarianMethodTest : public ::testing::Test
{
public:
        Matrix A1{{8, 4, 7},
                    {5, 2, 3},
                    {9, 4, 8}};

        Matrix A2{{2, 3, 4, 9},
                    {3, 3, 0, 1},
                    {1, 1, 2, 0}};

        Matrix A3{{96, 300, 300, 300, 300},
                    {0, 99, 300, 300, 300},
                    {300, 0, 300, 100, 300}};
};

TEST_F(HungarianMethodTest, square_matrix_hungarian_method)
{
    Matrix extended = addZeroColumnAndZeroRowToMatrix(A1);
    Matrix test = hungarianMethod(extended.cast<double>());

    Matrix result{{1, 0, 0},
                    {0, 0, 1},
                    {0, 1, 0}};

    for (int i = 0; i < test.rows(); ++i)
        for (int j = 0; j < test.cols(); ++j)
            ASSERT_EQ(result(i, j), test(i, j));
}

TEST_F(HungarianMethodTest, rectangle_matrix_hungarian_method)
{
    Matrix extended = addZeroColumnAndZeroRowToMatrix(A2);
    Matrix test = hungarianMethod(extended.cast<double>());

    Matrix result {{1, 0, 0, 0},
                    {0, 0, 1, 0},
                    {0, 0, 0, 1}};

    for (int i = 0; i < test.rows(); ++i)
        for (int j = 0; j < test.cols(); ++j)
            ASSERT_EQ(result(i, j), test(i, j));
}

TEST_F(HungarianMethodTest, tricky_rectangle_matrix_hungarian_method)
{
    Matrix extended = addZeroColumnAndZeroRowToMatrix(A3);
    Matrix test = hungarianMethod(extended.cast<double>());

    Matrix result {{1, 0, 0, 0, 0},
                    {0, 1, 0, 0, 0},
                    {0, 0, 0, 1, 0}};

    for (int i = 0; i < test.rows(); ++i)
        for (int j = 0; j < test.cols(); ++j)
            ASSERT_EQ(result(i, j), test(i, j));
}