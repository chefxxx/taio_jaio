//
// Created by Mateusz Mikiciuk on 18/11/2025.
//

#include <common.h>
#include <gtest/gtest.h>

#include "exact_solution_infra.h"

class MatricesTest : public ::testing::Test
{
public:
    Matrix A1;
    Matrix A2;
    long   v1{};
    long   v2{};

protected:
    void SetUp() override
    {
        A1 = Matrix{
            {1, 1},
            {1, 1},
        };
        A2 = Matrix{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}};
        v1 = A1.rows();
        v2 = A2.rows();
    }
};

TEST_F(MatricesTest, does_completeVerticesNumber_PreserveVerticesCount_WhenNoChange)
{
    const std::vector ks{1, 2, 3};
    v2 = completeVerticesNumber(v1, v2, ks[0]);
    ASSERT_EQ(v2, A2.rows());
    v2 = completeVerticesNumber(v1, v2, ks[1]);
    ASSERT_EQ(v2, A2.rows());
    v2 = completeVerticesNumber(v1, v2, ks[2]);
}

TEST_F(MatricesTest, does_completeVerticesNumber_CompleteVerticesCount_WhenNeeded_Small)
{
    constexpr int k = 4;
    v2              = completeVerticesNumber(v1, v2, k);
    ASSERT_EQ(v2, 4);
}

TEST_F(MatricesTest, does_completeVerticesNumber_CompleteVerticesCount_WhenNeeded_Big)
{
    constexpr int k = 5000;
    v2              = completeVerticesNumber(v1, v2, k);
    ASSERT_EQ(v2, 101);
}

TEST_F(MatricesTest, does_extendVertices_ExtendMatrix_WhenNeeded_Small)
{
    extendVertices(A2, 4);
    for (int i = 0; i < A2.rows(); i++) {
        for (int j = 0; j < A2.cols(); j++) {
            if (i < v2 && j < v2)
                ASSERT_EQ(A2(i, j), 1);
            else
                ASSERT_EQ(A2(i, j), 0);
        }
    }
}

TEST_F(MatricesTest, does_extendVertices_ExtendMatrix_WhenNeeded_Big)
{
    extendVertices(A2, 101);
    for (int i = 0; i < A2.rows(); i++) {
        for (int j = 0; j < A2.cols(); j++) {
            if (i < v2 && j < v2)
                ASSERT_EQ(A2(i, j), 1);
            else
                ASSERT_EQ(A2(i, j), 0);
        }
    }
}