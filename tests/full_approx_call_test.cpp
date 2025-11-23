//
// Created by mshamrai on 11/23/25.
//
#include <gtest/gtest.h>

#include "approximation_algorithm.h"


class FullApproxCall : public ::testing::Test
{
public:
    Matrix G1 {
            {0, 1, 0, 1},
                {1, 0, 1, 0},
                {0, 1, 0, 1},
                {1, 0, 1, 0}};

    Matrix G2 {
            {0, 1, 1, 0},
               {1, 0, 1, 0},
               {1, 1, 0, 1},
               {0, 0, 1, 0}};

    Matrix G3 {{0, 1, 1, 0, 0},
                    {1, 0, 0, 1, 0},
                    {1, 0, 0, 1, 1},
                    {0, 1, 1, 0, 1},
                    {0, 0, 1, 1, 0}};

    Matrix G4 {{0, 1, 0, 1, 0, 0, 0, 0},
                    {1, 0, 1, 0, 0, 0, 0, 0},
                    {0, 1, 0, 1, 0, 1, 0, 0},
                    {1, 0, 1, 0, 1, 0, 1, 0},
                    {0, 0, 0, 1, 0, 0, 0, 1},
                    {0, 0, 1 ,0, 0, 0, 1, 0},
                    {0, 0, 0, 1, 0, 1, 0, 1},
                    {0, 0, 0, 0, 1, 0, 1, 0},};
};

TEST_F(FullApproxCall, check_first_pair)
{
    auto extendedMatrix = approximationAlgorithm(G1, G2);

    for (int i = 0; i < G2.rows(); ++i, printf("\n"))
        for (int j = 0; j < G2.cols(); ++j)
            printf("%d (%d)   ", extendedMatrix(i, j), G2(i, j));
}

TEST_F(FullApproxCall, check_second_pair)
{
    auto extendedMatrix = approximationAlgorithm(G3, G4);

    for (int i = 0; i < G4.rows(); ++i, printf("\n"))
        for (int j = 0; j < G4.cols(); ++j)
            printf("%d (%d)   ", extendedMatrix(i, j), G4(i, j));
}