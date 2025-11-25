//
// Created by mshamrai on 11/23/25.
//
#include <gtest/gtest.h>

#include "approximation_algorithm.h"
#include "io_manager.h"

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

    printMatricesAfterAlgorithm(G2, extendedMatrix);
}

TEST_F(FullApproxCall, check_second_pair)
{
    auto extendedMatrix = approximationAlgorithm(G3, G4);

    printMatricesAfterAlgorithm(G4, extendedMatrix);
}