//
// Created by Mateusz Mikiciuk on 19/11/2025.
//

#ifndef SUBGRAPH_ISOMORPHISM_ARGS_H
#define SUBGRAPH_ISOMORPHISM_ARGS_H

#include <vector>

#include "eigen_port.h"

struct SI_Problem
{
    SI_Problem(const Matrix &t_A1, const Matrix &t_A2)
        : A1(t_A1)
        , A2(t_A2)
        , v1(t_A1.rows())
        , v2(t_A2.rows())
    {
    }
    const Matrix &A1;
    const Matrix &A2;
    long          v1;
    long          v2;
};

struct SI_State
{
    SI_State(const std::vector<bool> &t_cols, const Matrix &t_M, const long t_R)
        : cols(t_cols)
        , M(t_M)
        , R(t_R)
    {
    }
    void serialNextState(const size_t col)
    {
        M(R, static_cast<long>(col)) = 1;
        R++;
        cols[col] = true;
    }
    void serialPrevState(const size_t col)
    {
        cols[col] = false;
        R--;
        M(R, static_cast<long>(col)) = 0;
    }
    std::vector<bool> cols;
    Matrix            M;
    long              R;
};


#endif //SUBGRAPH_ISOMORPHISM_ARGS_H
