//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#include <gtest/gtest.h>

#include "eigen_port.h"
#include "common.h"

class GraphsFunctionsTest : public ::testing::Test
{
public:
    Matrix A11;
    Matrix A12;
    Matrix A2;
    Matrix validM;

protected:
    void SetUp() override
    {
        A11    = Matrix{{0, 2, 0}, {0, 0, 1}, {1, 0, 0}};
        A12    = Matrix{{0, 20, 0}, {0, 0, 3}, {7, 0, 0}};
        A2     = Matrix{{0, 3, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 1, 7}, {0, 0, 2, 0, 0}, {0, 2, 0, 0, 0}};
        validM = Matrix{{0, 0, 1, 0, 0}, {0, 0, 0, 0, 1}, {0, 1, 0, 0, 0}};
    }
};

TEST_F(GraphsFunctionsTest, does_checkIsomorphism_Returns_True_WhenIsomorphismExists)
{
    ASSERT_TRUE(checkIsomorphism(A11, A2, validM));
}

TEST_F(GraphsFunctionsTest, does_checkIsomorphism_Returns_False_WhenIsomorphismDoesNotExist)
{
    // this matrix represents an invalid mapping
    const auto M = Matrix{{0, 1, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 1}};
    ASSERT_FALSE(checkIsomorphism(A11, A2, M));
}

TEST_F(GraphsFunctionsTest, does_computeSubgraphFromMapping_computeValidMatrix)
{
    // this is the expected resulting matrix that represents subgraph of A2 isomorphic to A11
    const auto expected = Matrix{{0, 0, 0, 0, 0}, {0, 0, 1, 0, 0}, {0, 0, 0, 0, 2}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}};
    const auto A2prim   = computeSubgraphFromMapping(A11, validM);
    ASSERT_EQ(expected, A2prim);
}

TEST_F(GraphsFunctionsTest, does_computeExtension_Return_ValidExtensionMatrix_WhenEdgesAreMissing)
{
    // this matrix represents an expected result
    const auto expected = Matrix{{0, 0, 0, 0, 0}, {0, 0, 6, 0, 0}, {0, 0, 0, 0, 13}, {0, 0, 0, 0, 0}, {0, 1, 0, 0, 0}};
    const auto resultingExtension = computeExtension(A12, A2, validM);
    ASSERT_EQ(expected, resultingExtension);
}
